#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <locale.h>

//for scandir
#include <dirent.h>

//for stat()
#include <sys/stat.h>

//for getpid()
#include <sys/types.h>
#include <unistd.h>

#include <wchar.h>

int show_tree=1;
int depth = 0;
char root_path[256];
char file_list[50];

int pid =1;
char **flist;

int ignore(const char *name)
{
    if ( strstr(name, ".Trash")!=NULL || strcmp(".git", name) == 0 || strcmp(".", name) == 0 || strcmp("..", name) == 0 || strcmp("$Recycle.Bin", name) == 0 || strcmp("System Volume Information", name) == 0)
    {
        return 0;
    }
    return 1;
}

void repeat(int count, const char *s,char *buf)
{
    for (int i = 0; i < count; i++)
    {
        sprintf(buf,"%s%s", buf,s);
    }
}


int one (const struct dirent *unused)
{
    return 1;
}


#ifdef _WIN32
struct _stat st;
#elif __linux__
struct stat st;
#endif

int tree(const char *dir)
{
    depth++;
    FILE *fp = fopen(file_list, "a,css=UTF-8");

    char whole_path[256];

    struct dirent **eps;
    int n;
    n = scandir (dir, &eps, one, alphasort);
    if (n >= 0)
    {
        char buf[256];

        if(show_tree)
        {
            repeat(depth, "   ",buf);
        }
        int cnt;
        for (cnt = 0; cnt < n; ++cnt)
        {

            if (ignore(eps[cnt]->d_name) == 0)
            {
                continue;
            }

            memset(whole_path, '\0', sizeof(whole_path));

#ifdef _WIN32
            sprintf(whole_path, "%s\\%s", dir, p_dirent->d_name);
            if (eps[cnt]->d_type == 2)
#elif __linux__
                sprintf(whole_path, "%s/%s", dir, eps[cnt]->d_name);
            if (eps[cnt]->d_type == DT_DIR)
#endif
            {
#ifdef _WIN32
                _stat(p_dirent->d_name, &st);
#elif __linux__
                stat(eps[cnt]->d_name, &st);
#endif

                int pos=strlen(root_path)+1;
                fwprintf(fp,L"%s%s\n",buf,whole_path+pos);

                tree(whole_path);
            }
            else
            {

#ifdef _WIN32
                _stat(p_dirent->d_name, &st);
#elif __linux__
                stat(whole_path, &st);
#endif
                int pos=strlen(root_path)+1;
                fwprintf(fp,L"%s%s|%ld|%ld\n", buf,whole_path+pos,st.st_size,st.st_mtim.tv_sec);

            }
        }
    }
    fclose(fp);
    depth--;
    return 0;
}

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "en_US.UTF-8");

    if(argc == 2)
    {
        pid_t pid=getpid();
        sprintf(file_list,"/tmp/mysync.%d",pid);

        strcpy(root_path,argv[1]);
        tree(root_path);
    }
    return 0;
}

