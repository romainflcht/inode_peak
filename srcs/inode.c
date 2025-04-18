#include "inode.h"


void print_inode_info(STAT_t* s_buf)
{
    printf("\t- inode number: %ju\n", (uintmax_t)(s_buf->st_ino));
    printf("\t- hardlink: %ju\n", (uintmax_t)(s_buf->st_nlink)); 
    printf("\t- size: %ldo\n", s_buf->st_size);
    printf("\t- block count: %ld\n", s_buf->st_blocks); 
    printf("\t- uid: %d\n", s_buf->st_uid); 
    printf("\t- gid: %d\n", s_buf->st_gid); 
}


// * Print the inode id and the filename of each file contained in the 
// * directory.
// * @param: dirname: the name of the directory that we want to print.  
void print_dir_content(const char* dirname)
{
    DIR*        current_dir; 
    DIRENT_t*   d_buf; 

    // Open the directory and check if it opened correctly. 
    current_dir = opendir(dirname); 
    if (!current_dir)
        return; 

    printf("%s/\n", dirname);
    // Iterate through each file in the directory. 
    while ((d_buf = readdir(current_dir)))
    {
        // Print the inode id and the name of the file.
        printf("\t|- [%ju] %s\n", (uintmax_t)(d_buf->d_ino), d_buf->d_name); 
    } 

    // Free the memory.
    closedir(current_dir); 
    return; 
}


// * Print information about device. 
// * @param: s_buf*: the buffer containing inode data.
void print_node_info(STAT_t* s_buf)
{
    unsigned int major_id; 
    unsigned int minor_id;
    
    // Check if the interface is either a CHAR or BLOCK device. 
    if (!S_ISCHR(s_buf->st_mode) && !S_ISBLK(s_buf->st_mode))
        return; 

    // Get the major and minor that compose the device id. 
    major_id = major(s_buf->st_rdev);
    minor_id = minor(s_buf->st_rdev);

    // Print if it is a CHAR or a BLOCK device. 
    switch (s_buf->st_mode & S_IFMT)
    {
        case S_IFBLK:
            printf("Block device\n"); 
            break;

        case S_IFCHR: 
            printf("Char device\n"); 
            break; 
    }

    // Print the device id. 
    printf("ID of device:  [%d,%d]\n", major_id, minor_id);
    return; 
}