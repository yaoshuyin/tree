#include <stdio.h>
#include <string.h>
#include <dirent.h>

int depth = 0;

int ignore(const char *name)
{
    if (strcmp(".", name) == 0 || strcmp("..", name) == 0 || strcmp("$Recycle.Bin", name) == 0 || strcmp("System Volume Information", name) == 0)
    {
        return 0;
    }
    return 1;
}

void repeat(int count, const char *s)
{
    for(int i=0; i<count; i++)
    {
        printf("%s",s);
    }
}

int tree(const char *argDir)
{
    depth++;

    char path[256];
    char path2[256];

#ifdef _WIN32
    struct _dirent *pDir = NULL;
    _DIR *dir = _opendir(argDir);
#elif __linux__
    struct dirent *pDir = NULL;
    DIR *dir = opendir(argDir);
#endif

    if (dir != NULL)
    {
        sprintf(path, ("%s", argDir));

#ifdef _WIN32
        while ((pDir = _readdir(dir)) != NULL)
#elif __linux__
        while ((pDir = readdir(dir)) != NULL)
#endif
        {
            if (ignore(pDir->d_name) == 0)
            {
                continue;
            }

            repeat(depth, "\t");
#ifdef _WIN32
            if (pDir->d_type == 2)
            {
                sprintf(path2, "%s\\%s", path, pDir->d_name);
#elif __linux__

            if (pDir->d_type == DT_DIR)
            {
                sprintf(path2, "%s/%s", path, pDir->d_name);
#endif

                printf("%s\n", path2);

                tree(path2);
            }
            else
            {
                printf("%s\n", pDir->d_name);
            }
        }
    }
    depth--;
    return 0;
}

int main(int argc, char **argv)
{
    if(argc == 2)
    {
        printf("%s\n", argv[1]);
        tree(argv[1]);
    }
    return 0;
}
