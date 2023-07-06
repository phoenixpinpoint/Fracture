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

/**
 * @brief Get the Current working directory
 * 
 * @return char* 
 */
char* GET_CWD()
{
  char* cwd = (char*)malloc(FS_PATH_MAX*sizeof(char));
  if (getcwd(cwd, FS_PATH_MAX) != NULL) {
    return cwd;
  } else {
    return "-1";
  }
}

/**
 * @brief Create a directory list object
 * 
 * @return DIRECTORYLIST* 
 */
DIRECTORYLIST* CREATE_DIRECTORY_LIST()
{
    //Create a new listInstance Object
    DIRECTORYLIST* listInstance = (DIRECTORYLIST*)malloc(sizeof(DIRECTORYLIST));
    listInstance->length = 0;
    listInstance->directories = 0;

    // Return the created list.
    return listInstance;
}


/**
 * @brief List files in a directory. (ls)
 * 
 * @param path
 * @return DIRECTORYLIST*
 */
DIRECTORYLIST* LIST_FILES(char* path)
{
    //Create a DIR pointer and opendir.
    DIR * dp = opendir(path);

    //Create DIRECTORYLIST to store DIRENT structs
    DIRECTORYLIST *directoryList = CREATE_DIRECTORY_LIST();

    //If no valid pointer returned.
    if(!dp) {
        return directoryList;
    }

    //Create a directory entry structure pointer
    struct dirent * ep;

    char newdir[FS_PATH_MAX];
    while((ep = readdir(dp)))
        if(strncmp(ep->d_name, ".", 1))
            ADD_DIRECTORY(directoryList, ep);
    
    closedir(dp);
    return directoryList;
}

/**
 * @brief Add Directory Entry to Existing List of entries
 * 
 * @param list 
 * @param directory
 */
void ADD_DIRECTORY(DIRECTORYLIST *list, struct dirent *directory)
{
    //If first directory
    if(list->length == 0)
    {
        list->directories = (struct dirent**)malloc(sizeof(struct dirent*));
        list->directories[0] = directory;
        list->length = 1;
    }
    // //If additional directory
    else{
        list->directories = (struct dirent**)realloc(list->directories, (list->length+1)*sizeof(struct dirent*));
        list->directories[list->length] = directory;
        list->length = list->length + 1;
    }

    return;
}

/**
 * @brief Get the directory object
 * 
 * @param list 
 * @param index 
 * @return struct dirent* 
 */
struct dirent* GET_DIRECTORY(DIRECTORYLIST *list, int index)
{
    if (list->directories[index])
    {
        return list->directories[index];
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Prints out the Directory List
 * 
 * @param list 
 */
void PRINT_DIRECTORY_LIST(DIRECTORYLIST *list)
{
    printf("PRINT_DIRECTORY_LIST\n====================\n");
    for (int iteration = 0; iteration < list->length-1; iteration++)
    {
        printf("Index:%d, Value:*%s*\n", iteration, list->directories[iteration]->d_name);
    }
    printf("====================\n");
}