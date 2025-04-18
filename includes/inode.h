#ifndef _INODE_H_
#define _INODE_H_

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <dirent.h>


#define BUF_LEN 256

// * _ TYPE DEFINITIONS ________________________________________________________
typedef struct stat STAT_t; 
typedef struct dirent DIRENT_t; 


// * _ FUNCTION DECLARATIONS ___________________________________________________
// * Print every information depending on file type. 
// * @param: s_buf*  : buffer containing stat info of the file. 
// * @param: filename: path of the file. 
void print_inode_info(STAT_t* s_buf, const char* filename);


// * Print the inode id and the filename of each file contained in the 
// * directory.
// * @param: dirname: the name of the directory that we want to print.  
void print_dir_content(const char* dirname); 


// * Print information about device. 
// * @param: s_buf*: the buffer containing inode data.
void print_device_info(STAT_t* s_buf); 

// * Print the destination of a symbolic link. 
// * @param: filename: the name of the symbolic link to print. 
void print_symlink_info(const char* filename);


// * Print permission of file in ls format. 
// * @param: s_buf*: file data where we get permissions. 
void print_perm_info(STAT_t* s_buf); 
#endif