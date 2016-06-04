#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "tree.h"


#define PORT 5555
#define MAXMSG 512

int make_socket (uint16_t port)
{
    int sock;
    struct sockaddr_in name;
    /* Create the socket. */
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror ("socket");
        exit (EXIT_FAILURE);
    }
    /* Give the socket a name. */
    name.sin_family = AF_INET;
    name.sin_port = htons (port);
    name.sin_addr.s_addr = htonl (INADDR_ANY); //INADDR_ANY 0.0.0.0
    if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
    {
        perror ("bind");
        exit (EXIT_FAILURE);
    }
    return sock;
}

int read_from_client(int fd)
{
    char buffer[MAXMSG];
    int nbytes=read(fd, buffer, MAXMSG-1);
    if(nbytes <0)
    {
        perror("read");
        exit(EXIT_FAILURE);
    }
    else if(nbytes == 0)
    {
        return -1;
    }
    else
    {
        fprintf(stderr,"from client: %s\n", buffer);
        char buf_to_client[256]="sssssss\n";
        send(fd, buf_to_client,strlen(buf_to_client), 0&MSG_DONTWAIT);

        sleep(1);
        pid_t pid=getpid();
        char tmp_file[60], root_path[60];
        sprintf(tmp_file,"/tmp/mysync.%d",pid);
        strcpy(root_path,"/data/Progs");
        tree(root_path, tmp_file);


        FILE *fp = fopen(tmp_file, "r,css=UTF-8");
        if(fp != NULL)
        {
            char buf[256];
            while(fgets(buf, sizeof(buf),fp)!=NULL)
            {

                send(fd, buf,strlen(buf), 0&MSG_DONTWAIT);
                bzero(buf,sizeof(buf));
            }
            fclose(fp);
            strcpy(buf,".....finish....\n");
            send(fd, buf,strlen(buf), 0&MSG_DONTWAIT);
        }
    }
    return 0;
}

int main(void)
{
    fd_set active_fd_set, read_fd_set;
    int i;
    struct sockaddr_in clientname;

    socklen_t size;
    int sock = make_socket(PORT);

    if(listen(sock, 1) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&active_fd_set);
    FD_SET(sock,&active_fd_set);

    while(1)
    {
        read_fd_set = active_fd_set;

        if(select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
        {
            perror("select");
            exit(EXIT_FAILURE);
        }

        for(i=0; i<FD_SETSIZE; ++i)
        {
            if(FD_ISSET(i, &read_fd_set))
            {
                if(i == sock)
                {
                    int newc;
                    size = sizeof(clientname);
                    newc = accept(sock, (struct sockaddr *) &clientname, &size);
                    if(newc < 0)
                    {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
                    fprintf(stderr, "connect from host %s, port %hd.\n", inet_ntoa(clientname.sin_addr), ntohs(clientname.sin_port));
                    FD_SET(newc, &active_fd_set);
                }
                else
                {
                    if(read_from_client(i)<0)
                    {
                        close(i);
                        FD_CLR(i, &active_fd_set);
                    }
                }
            }
        }
    }


    return 0;
}
