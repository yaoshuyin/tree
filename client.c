#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 5555
#define MESSAGE "Yow!!! Are we having fun yet?!?"
#define SERVERHOST "localhost"

void init_sockaddr (struct sockaddr_in *name, const char *hostname, uint16_t port)
{
    struct hostent *hostinfo;
    name->sin_family = AF_INET;
    name->sin_port = htons (port);
    hostinfo = gethostbyname (hostname);
    if (hostinfo == NULL)
    {
        fprintf (stderr, "Unknown host %s.\n", hostname);
        exit (EXIT_FAILURE);
    }
    name->sin_addr = *(struct in_addr *) hostinfo->h_addr;
}

void write_to_server (int sockfd)
{
    int nbytes;
    nbytes = write (sockfd, MESSAGE, strlen (MESSAGE) + 1);
    if (nbytes < 0)
    {
        perror ("write");
        exit (EXIT_FAILURE);
    }

    char buf[256];

    while(recv(sockfd, buf, sizeof(buf)-1,0)>0)
    {
        fprintf(stderr,"%s",buf);
        if(strstr(buf,".....finish....") !=NULL)
            break;
        memset(buf,'\0',sizeof(buf));
    }

}

int main (void)
{
    int sock;
    struct sockaddr_in servername;

    /* Create the socket. */
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror ("socket (client)");
        exit (EXIT_FAILURE);
    }

    //timeout for recv
    struct timeval timeout = {.tv_sec = 100, .tv_usec = 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(struct timeval));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(struct timeval));
    //~timeout for recv

    /* Connect to the server. */
    init_sockaddr (&servername, SERVERHOST, PORT);
    if (0 > connect (sock, (struct sockaddr *) &servername, sizeof (servername)))
    {
        perror ("connect (client)");
        exit (EXIT_FAILURE);
    }

    /* Send data to the server. */
    write_to_server (sock);
    close (sock);

    exit (EXIT_SUCCESS);
}
