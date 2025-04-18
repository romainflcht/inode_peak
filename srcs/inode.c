#include "inode.h"


// * Print every information depending on file type. 
// * @param: s_buf*  : buffer containing stat info of the file. 
// * @param: filename: path of the file. 
void print_inode_info(STAT_t* s_buf, const char* filename)
{
    // Print inode id, name and permissions. 
    printf("\n\x1b[1m[%ju] \x1b[34m%s\x1b[0m | ", (uintmax_t)(s_buf->st_ino), filename); 
    print_perm_info(s_buf); 

    // print general info. 
    printf("\t- hardlink: %ju\n", (uintmax_t)(s_buf->st_nlink)); 
    printf("\t- size    : %ld bytes\n", s_buf->st_size);
    printf("\t- uid     : %d\n", s_buf->st_uid); 
    printf("\t- gid     : %d\n", s_buf->st_gid); 

    // Print type specific info. 
    switch (s_buf->st_mode & S_IFMT)
    {
        case S_IFBLK: 
        case S_IFCHR: 
            printf("\t- type    : device.\n"); 
            print_device_info(s_buf);
            break;
    
        case S_IFDIR: 
        printf("\t- type    : directory.\n"); 
            print_dir_content(filename); 
          break;
    
        case S_IFLNK:
            printf("\t- type    : symbolic link.\n"); 
            print_symlink_info(filename); 
            break;
    
        case S_IFREG: 
            printf("\t- type    : regular file.\n"); 
            break;
    
        default: 
            printf("\t- type    : unknown.\n");  
            break;
    }

    return;
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

    printf("\x1b[1m\t%s/\x1b[0m\n", dirname);
    // Iterate through each file in the directory. 
    while ((d_buf = readdir(current_dir)))
    {
        // Print the inode id and the name of the file.
        printf(
            "\x1b[1m\t\t|- [%ju] \x1b[0;34m%s\x1b[0m\n", 
            (uintmax_t)(d_buf->d_ino), 
            d_buf->d_name
        ); 
    } 

    // Free the memory.
    closedir(current_dir); 
    return; 
}


// * Print information about device. 
// * @param: s_buf*: the buffer containing inode data.
void print_device_info(STAT_t* s_buf)
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
    printf("\t- mode    : "); 
    switch (s_buf->st_mode & S_IFMT)
    {
        case S_IFBLK:
            printf("block device.\n"); 
            break;

        case S_IFCHR: 
            printf("char device.\n"); 
            break; 
    }

    // Print the device id. 
    printf(
        "\t- id      : [%d;%d] \x1b[3;30m[major;minor]\x1b[0m\n", 
        major_id, 
        minor_id
    );
    return; 
}


// * Print the destination of a symbolic link. 
// * @param: filename: the name of the symbolic link to print. 
void print_symlink_info(const char* filename)
{
    char    buf[BUF_LEN];
    ssize_t retval; 
    
    // Get the symlink destination. 
    retval = readlink(filename, buf, BUF_LEN - 1);
    if (retval < 0)
        return; 

    // Adding the null char to terminate the char. 
    buf[retval] = '\0'; 
    
    // Print the destination to stdout. 
    printf("\t- symlink : %s\n", buf); 
    return; 
}


// * Print permission of file in ls format. 
// * @param: s_buf*: file data where we get permissions. 
void print_perm_info(STAT_t* s_buf)
{
    // Read, write, exec from owner. 
    printf("\x1b[1;35m"); 
    printf((s_buf->st_mode & S_IRUSR) ? "r" : "-");
    printf((s_buf->st_mode & S_IWUSR) ? "w" : "-");
    printf((s_buf->st_mode & S_IXUSR) ? "x " : "- ");
    
    // Read, write, exec from groups. 
    printf("\x1b[1;36m"); 
    printf((s_buf->st_mode & S_IRGRP) ? "r" : "-");
    printf((s_buf->st_mode & S_IWGRP) ? "w" : "-");
    printf((s_buf->st_mode & S_IXGRP) ? "x " : "- ");
    
    // Read, write, exec from others. 
    printf("\x1b[1;33m"); 
    printf((s_buf->st_mode & S_IROTH) ? "r" : "-");
    printf((s_buf->st_mode & S_IWOTH) ? "w" : "-");
    printf((s_buf->st_mode & S_IXOTH) ? "x " : "- ");
    printf("\x1b[0m\n");
    return; 
}
