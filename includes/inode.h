#ifndef _INODE_H_
#define _INODE_H_

#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <dirent.h>

// * _ TYPE DEFINITIONS ________________________________________________________
typedef struct stat STAT_t; 
typedef struct dirent DIRENT_t; 


// * _ FUNCTION DECLARATIONS ___________________________________________________
void print_inode_info(STAT_t* s_buf);


// * Print the inode id and the filename of each file contained in the 
// * directory.
// * @param: dirname: the name of the directory that we want to print.  
void print_dir_content(const char* dirname); 


// * Print information about device. 
// * @param: s_buf*: the buffer containing inode data.
void print_node_info(STAT_t* s_buf); 
#endif