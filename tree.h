//fopen,fwprintf,sprintf
#include <stdio.h>
#include <stdlib.h>

//memset,strlen
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

//fwprintf
#include <wchar.h>

/**
 * return:
 *     >0 the number of wide characters written
 *     -1 when an error
 */
int c2w(wchar_t *w, char *c);

int ignore(const char *name);

void repeat(int count, const char *s,char *buf);


int one (const struct dirent *dir);


int tree(const char *dir, const char *tmp_file);
