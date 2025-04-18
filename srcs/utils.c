#include "utils.h"


// * Print the usage of the progam in case no arguments where passed. 
void usage(void)
{
    printf("\x1b[1;31musage: %s [file1] [file2]...\x1b[0m\n", PROG_NAME);
    return;  
}