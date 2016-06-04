#include <stdio.h>
#include <string.h>


void arr_intersection(char *arr1[], char *arr2[])
{
    char **p = arr1;
    char **p2 = arr2;
    int eq=0;
    while(*p!=NULL)
    {
        p2 = arr2;
        while(*p2!=NULL)
        {
                if(strcmp(*p,*p2) == 0)
                {
                    printf("%s\n",*p2);
                    break;
                }
                p2++;
        }

        p++;
    }
}

void arr_ldiff(char *arr1[], char *arr2[])
{
    char **p = arr1;
    char **p2 = arr2;
    int eq=0;
    while(*p!=NULL)
    {
        p2 = arr2;
        while(*p2!=NULL)
        {
            if(strcmp(*p,*p2) == 0)
            {
                eq=1;
                break;
            }
            p2++;
        }

        if(eq == 0)
            printf("%s\n",*p);
        else
            eq = 0;
        p++;
    }
}

void arr_union(char *arr1[], char *arr2[]){
}

void arr_difference(char *arr1[], char *arr2[]){
    arr_ldiff(arr1, arr2);
    arr_ldiff(arr2, arr1);
}

int main()
{
    char *arr1[]={
        "a",
        "b",
        "c",
        "d",
        "4",
        "7",
        "9",
        NULL
    };

    char *arr2[]={
        "a",
        "e",
        "b",
        "d",
        "1",
        "3",
        NULL
    };

    printf("%ld", sizeof(arr1));
    //set(arr1,arr2,1);

    printf("\ndifference:\n");
    arr_difference(arr1,arr2);

    printf("\nldiff:\n");
    arr_ldiff(arr2,arr1);

    printf("\nintersection\n");
    arr_intersection(arr1, arr2);

    return 0;
}
