/**
 * @file fs.h
 * @author Adam Guthrie
 * @brief fs.h
 * 
 *  Header file to include the entirety of the File System Utils module.
 * 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef FS_H
#define FS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <string.h>

#define FS_PATH_MAX 1024
//#define FS_ERROR_CODE_SIZE 3

/**
 * @brief DIRECTORYLIST
 * DIRECTORYLIST is a structure that stores length which is the number of directories in the list.
 * As well as an "array" of pointers that are the directory entry structs.
 */
typedef struct DIRECTORYLIST {
    int length;
    struct dirent ** directories
} DIRECTORYLIST;

/**
 * @brief Get the Current working directory
 * 
 * @return char* 
 */
char* GET_CWD();

/**
 * @brief Reads the content of the passed filepatch
 * 
 * @param path
 * @return char* 
 */
char* READ_FILE(char* path);

/**
 * @brief Create a directory list object
 * 
 * @return DIRECTORYLIST* 
 */
DIRECTORYLIST* CREATE_DIRECTORY_LIST();

/**
 * @brief List files in a directory. (ls)
 * @param path
 * @return char* 
 */
DIRECTORYLIST* LIST_FILES(char* path);

/**
 * @brief Add Directory Entry to Existing List of entries
 * 
 * @param list 
 * @param directory
 */
void ADD_DIRECTORY(DIRECTORYLIST *list, struct dirent *directory);

/**
 * @brief Get the directory object
 * 
 * @param list 
 * @param index 
 * @return struct dirent*
 */
struct dirent* GET_DIRECTORY(DIRECTORYLIST *list, int index);

/**
 * @brief Prints out the Directory List
 * 
 * @param list 
 */
void PRINT_DIRECTORY_LIST(DIRECTORYLIST *list);

#endif