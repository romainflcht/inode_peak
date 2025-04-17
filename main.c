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
            return 1; 

        retval = lstat(argv[i], &sb); 
        if (retval < 0)
            return 1; 

        printf("INODE ID: %ld\n", sb.st_ino); 
        i++;
        
        printf("\tIs a file? %d\n", S_ISREG(sb.st_mode)); 
        printf("\tIs a dir?  %d\n", S_ISDIR(sb.st_mode)); 
    }

    return 0; 
}