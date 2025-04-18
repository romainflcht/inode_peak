#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "inode.h"
#include "utils.h"

int main(int argc, char** argv)
{
    int     retval; 
    int     i; 
    STAT_t  s_buf; 

    // Check if arguments where passed to the program. 
    if (argc <= 1)
    {
        usage(); 
        return -1; 
    }


    // Iteration through each argument and print informations. 
    i = 1; 
    while (i < argc)
    {
        // Get stat info from a file. 
        retval = lstat(argv[i], &s_buf); 
        if (retval < 0)
        {
            printf(
                "\n\x1b[1;31mAn error occured while processing \x1b[37m%s\x1b[31m are you sure the file exist?\x1b[0m\n", 
                argv[i]
            ); 
            i++; 
            continue; 
        }

        print_inode_info(&s_buf, argv[i]); 
        i++;
    }

    printf("\n\n\x1b[1mGoodbye :)\n\x1b[30mMade by romain.\x1b[0m\n"); 
    return 0; 
}