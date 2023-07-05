/**
 * @file fs.c
 * @author Adam Guthrie
 * @brief fs.c
 * 
 *  Source file to include the entirety of the File System Utils module.
 * 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "fs.h"

/**
 * @brief Reads the content of the passed filepatch
 * 
 * @param path
 * @return char* 
 */
char* READ_FILE(char* path)
{
    char * buffer = 0;
    long length;
    FILE * f;
    f = fopen (path, "rb");
    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc (length+1);
        if (buffer)
        {
            fread (buffer, 1, length, f);
        }
        buffer[length] = '\0';
        fclose (f);
    }
    else
    {
        return "-1";
    }

    if (buffer)
    {
        return buffer;
    }
    else
    {
        return "-2";
    }
}
