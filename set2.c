#include <stdio.h>
#include <string.h>

void arr_intersection(char arr1[][256], int lines1, char arr2[][256], int lines2)
{
    for(int i=0; i<lines1; i++)
    {
        if(strlen(arr1[i])>0)
        {
            for(int j=0; j<lines2; j++)
            {
                if(strlen(arr2[j])>0 && strcmp(arr1[i],arr2[j]) == 0)
                {
                    printf("%s\n",arr2[j]);
                    break;
                }
            }
        }
    }
}

int strpos(char *s, const char *sub)
{
    char *p = strstr(s,sub);
    if(p!=NULL)
    {
        char buf[256];
        bzero(buf,sizeof(buf));
        int pos = strlen(s)-strlen(p);
        return pos;
    }
    return -1;
}

int split(char *s,const char *sep,char *arg_buf)
{
    int pos = strpos(s, sep);

    if(pos != -1)
    {
        char buf[256];
        bzero(buf,sizeof(buf));
        strncpy(buf,s,pos);
        strcpy(arg_buf,buf);
        //printf("%s\n", buf);
        return pos;
    }
    else
    {
        strcpy(arg_buf,s);
        return 0;
    }
}

void arr_ldiff(char arr1[][256], int lines1, char arr2[][256], int lines2)
{
    for(int i=0; i<lines1; i++)
    {
        if(strlen(arr1[i])>0)
        {
            int eq=3;
            const char *sep = "|";
            char buf[256],buf2[256];
            bzero(buf,sizeof(buf));
            bzero(buf2,sizeof(buf2));

            split(arr1[i],sep,buf);
            sprintf(buf2,"%s|",buf);
            int j=0;
            for(; j<lines2; j++)
            {
                if(strlen(arr2[j])>0)
                {
                    if( strcmp(arr1[i],arr2[j]) == 0)
                    {
                        eq=1;
                        break;
                    }
                    else
                    {
                        if(strstr(arr2[j], buf2) == arr2[j]) //如果找到文件名,则大小或日期不同
                        {
                            eq=2; //文件名相同，但日期或大小不同
                            break;
                        }
                    }
                }
            }

            if(eq == 1)
            {
                printf("equal: %s\n", arr1[i]);
            }
            else if(eq == 2)
            {
                printf("difference: %s ==> %s\n", arr1[i],arr2[j]);
            }
            else if(eq == 3)
            {
                printf("only in arr1: %s\n", arr1[i]);
            }
        }
    }
}

void arr_diff(char arr1[][256], int lines1, char arr2[][256], int lines2)
{
    /**
     * arr1 : have  arr2 : no    arr1 is more than arr2
     * arr1 : have  arr2 : have  different
     * ==>  copy  arr1  to  arr2
     */
    arr_ldiff(arr1,lines1,arr2,lines2);


    /**
     * arr2 : have  arr1 : no     arr2 is more than arr1  ==>  arr2 need delete
     * arr1 : have  arr2 : have   different  ==>  need copy to arr2
     */
    //arr_ldiff(arr2,lines2,arr1,lines1);
}
