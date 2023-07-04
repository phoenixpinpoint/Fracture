/**
 * @file headers.c
 * @author Adam Guthrie
 * @brief headers.h
 * 
 *  Headers stores a struct template for keeping headers in both requests and responses.
 * 
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "headers.h"

/**
 * @brief CREATE_HEADER
 * CREATE_HEADER takes two string array literals and returns a pointer to a newly created
 * header object.
 * @return HEADER *
 */
HEADER* CREATE_HEADER(char* key, char* value)
{
    //Create an instance pointer.
    HEADER *instance = (HEADER*)malloc(sizeof(HEADER));

    //If Key is a valid value
    if (strlen(key) > 0)
    {
        instance->key = (char*)malloc(strlen(key)+1*sizeof(char));
        strncpy(instance->key, key, strlen(key)+1);
    }
    else {
        return -1;
    }

    //If Value is a valid value.
    if(strlen(value) > 0)
    {
        instance->value = (char*)malloc(strlen(value)+1*sizeof(char));
        strncpy(instance->value, value, strlen(value)+1);
    }
    else {
        return -1;
    }

    //Return the Resulting Pointer
    return instance;
}

/**
 * @brief FREE_HEADER
 * FREE_HEADER frees the the header struct an values
 * @param h 
 */
void FREE_HEADER(HEADER* h)
{
    if(h->key)
    {
        free(h->key);
    }
    if(h->value)
    {
        free(h->value);
    }
    if(h)
    {
        free(h);
    }
    return;
}

/**
 * @brief Set the key object
 * 
 * @param h 
 * @param key 
 */
void SET_KEY(HEADER *h, char* key)
{
    // If there is key value free it.
    if(h->key)
    {
        free(h->key);
        h->key = 0;
    }
    
    //If there is a key value
    if(key)
    {
        h->key = (char*)malloc(strlen(key)*sizeof(char));
        strncpy(h->key, key, strlen(key));
    }
    return;
}

/**
 * @brief Set the value object
 * 
 * @param h 
 * @param value 
 */
void SET_VALUE(HEADER *h, char* value)
{
    //If there is a value string free it
    if(h->value)
    {
        free(h->value);
        h->value = 0;
    }

    //Value passed to the function
    if(value)
    {
        h->value = (char*)malloc(strlen(value)*sizeof(char));
        strncpy(h->value, value, strlen(value));
    }
}

/**
 * @brief Create a header list object
 * 
 * @return HEADERS* 
 */
HEADERLIST* CREATE_HEADER_LIST()
{
    //Create a new listInstance Object
    HEADERLIST* listInstance = (HEADERLIST*)malloc(sizeof(HEADERLIST));
    listInstance->length = 0;
    listInstance->headers = 0;

    // Return the created list.
    return listInstance;
}

/**
 * @brief Add Header to Existing List of Headers
 * 
 * @param list 
 * @param header 
 */
void ADD_HEADER(HEADERLIST *list, HEADER *header)
{
    //If first header
    if(list->length == 0)
    {
        list->headers = (HEADER**)malloc(sizeof(HEADER*));
        list->headers[0] = header;
        list->length = 1;
    }
    //If additional header
    else{
        list->headers = (HEADER**)realloc(list->headers, (list->length+1)*sizeof(HEADER*));
        list->headers[list->length] = header;
        list->length = list->length + 1;
    }

    return;
}

/**
 * @brief Get the header object
 * 
 * @param list 
 * @param index 
 * @return HEADER* 
 */
HEADER* GET_HEADER(HEADERLIST *list, int index)
{
    if (list->headers[index])
    {
        return list->headers[index];
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Get the header by key object
 * 
 * @param list 
 * @param key 
 * @return HEADER* 
 */
HEADER* GET_HEADER_BY_KEY(HEADERLIST *list, char* key)
{
    //If there are keys and headers
    if(strlen(key) > 0 && list->headers)
    {
        for(int iteration = 0; iteration < list->length; iteration++)
        {
            if(strcmp(list->headers[iteration]->key, key) == 0)
            {
                return list->headers[iteration];
            }
            return -1;
        }
    }
    else {
        return 0;
    }
}

/**
 * @brief removes header at a given index
 * 
 * @param list 
 * @param index 
 */
void REMOVE_HEADER(HEADERLIST *list, int index)
{
    //Handle Single Header Arrays
    if (index == 0 && list->length == 1)
    {
        free(list->headers);
        list->headers = 0;
        list->length = 0;
    }

    else {
        //For each entry after index, move up one and finally reallocate the array.
        for (int iteration = index; iteration < list->length-1; iteration++)
        {
            list->headers[index] = list->headers[index+1];
        }

        list->length = list->length - 1;
        list->headers = (HEADERLIST**)realloc(list->headers, list->length*sizeof(HEADER*));
    }

    return;
}

/**
 * @brief removes header at a given key
 * 
 * @param list 
 * @param key 
 */
void REMOVE_HEADER_BY_KEY(HEADERLIST *list, char* key)
{
    int indexToRemove = GET_HEADER_INDEX(list ,key);
    if(indexToRemove >= 0)
    {
        REMOVE_HEADER(list, indexToRemove);
    }
}

/**
 * @brief Get the header object index
 * 
 * @param list 
 * @param key 
 * @return int 
 */
int GET_HEADER_INDEX(HEADERLIST *list, char* key)
{
    //If there are keys and headers
    if(key && list->headers)
    {
        for(int iteration = 0; iteration < list->length-1; iteration++)
        {
            if(strcmp(list->headers[iteration]->key, key) == 0)
            {
                return iteration;
            }
        }
    }
    else {
        return -1;
    }
}

/**
 * @brief Prints out the Header List
 * 
 * @param list 
 */
void PRINT_HEADER_LIST(HEADERLIST *list)
{
    printf("PRINT_HEADER_LIST\n====================\n");
    for (int iteration = 0; iteration < list->length-1; iteration++)
    {
        printf("Index:%d, Key:*%s*, Value:*%s*\n", iteration, list->headers[iteration]->key, list->headers[iteration]->value);
    }
    printf("====================\n");
}

/**
 * @brief Frees the Header list structure
 * NOTE: does not free the HEADERs themselves.
 * @param list 
 */
void FREE_HEADER_LIST(HEADERLIST *list)
{
    if (list->headers)
    {
        free(list->headers);
    }

    if (list)
    {
        free(list);
    }
}
