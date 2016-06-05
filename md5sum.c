#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
//Usage:
//   Compile (-l must put at the end of line):
//       gcc -Wall md5sum.c -o md5sum -lcrypto -lssl
//
//   char buf[64];
//   md5sum("a.txt", buf);
//   printf("a.txt %s\n", buf);

int md5sum(const char *fname, char *buf)
{
    unsigned char c[MD5_DIGEST_LENGTH];
    int i;
    FILE *inFile = fopen (fname, "rb");
    MD5_CTX mdContext;
    int bytes;
    unsigned char data[1024];

    if (inFile == NULL) {
        printf ("%s can't be opened.\n", fname);
        return -1;
    }

    MD5_Init (&mdContext);
    while ((bytes = fread (data, 1, 1024, inFile)) != 0)
        MD5_Update (&mdContext, data, bytes);
    MD5_Final (c,&mdContext);

    char buf2[64];
    for(i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
        sprintf(buf2, "%02x", c[i]);
        strncat(buf,buf2,strlen(buf2));
    }
    fclose (inFile);
    return 0;
}
