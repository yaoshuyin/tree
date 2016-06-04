#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "set.h"

int main()
{
    FILE *fp1 = fopen("a.txt","r,css=UTF-8");
    FILE *fp2 = fopen("b.txt","r,css=UTF-8");

    char buf_file1[256];
    char buf_file2[256];

    int lines_file1=0;
    int lines_file2=0;

    size_t max_line_len=0;

    //get lines and max_line_len of file1
    while(fgets(buf_file1,sizeof(buf_file1),fp1)!=NULL){
        lines_file1++;
    //    max_line_len=strlen(buf_file1)>max_line_len?strlen(buf_file1):max_line_len;
    }

    //create array for file1
    char arr_lines1[lines_file1][256];

    //file array for file1 lines
    rewind(fp1);
    lines_file1=0;
    while(fgets(buf_file1,sizeof(buf_file1),fp1)!=NULL){
        strcpy(arr_lines1[lines_file1++], buf_file1);
    }
    fclose(fp1);

    /////////////////////////////////////////////


    //get lines and max_line_len of file2
    while(fgets(buf_file2,sizeof(buf_file2),fp2)!=NULL){
        lines_file2++;
    //    max_line_len=strlen(buf_file2)>max_line_len?strlen(buf_file2):max_line_len;
    }

    //create array for file2
    char arr_lines2[lines_file2][256];

    //file array for file2 lines
    rewind(fp2);
    lines_file2=0;
    while(fgets(buf_file2,sizeof(buf_file2),fp2)!=NULL){
        strcpy(arr_lines2[lines_file2++], buf_file2);
    }

    arr_diff(arr_lines1, lines_file1, arr_lines2, lines_file2);

    fclose(fp2);
    //while(1) {
    //   sleep(3);
    //}
    return 0;
}
