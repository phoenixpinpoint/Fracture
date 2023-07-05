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

#ifndef fs_H
#define fs_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Reads the content of the passed filepatch
 * 
 * @param patch
 * @return char* 
 */
char* READ_FILE(char* patch);

#endif