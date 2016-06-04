#include <stdio.h>
#include <string.h>
#include "tree.h"
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    setlocale(LC_ALL, "en_US.UTF-8");

        tree("/data/Progs", "/tmp/a.txt");
    return 0;
}
