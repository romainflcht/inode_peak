#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "inode.h"


int main(int argc, char** argv)
{
    int     retval; 
    int     i; 
    STAT_t  sb; 

    printf("ARGC: %d at %s\n", argc, *argv); 

    i = 1; 

    while (i < argc)
    {
        retval = access(argv[i], W_OK); 
        if (retval < 0)
        {
            printf("No access to %s\n", argv[i]); 
            i++; 
            continue;
        } 

        retval = lstat(argv[i], &sb); 
        if (retval < 0)
            return 1; 

        print_inode_info(&sb); 
        i++;
    }

    return 0; 
}