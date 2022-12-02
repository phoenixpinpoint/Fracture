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
 * @brief ADD_HEADERS
 *  * ADD_HEADERS takes a HEADERS list and a HEADER and adds the HEADER to HEADERS. 
 * If there isn't any current headers it allocates memory for the user. 
 * IF there is it reallocates and adds the header.
 * @param list 
 * @param header 
 * @return HEADERS 
 */
HEADERS ADD_HEADER(HEADERS list, HEADER header)
{
    //Store the lenght for ease of use later.
    int length = list.length;
    //Handle a new list
    if (length < 1)
    {
        //Allocate a pointer for header
        HEADER* h = calloc(1, sizeof(HEADER));
        //Set the Values
        h->key = header.key;
        h->value = header.value;
        //Set the list values for HEADERS
        list.length = 1;//Set the length to 1
        //Allocate the poitner to pointer.
        list.headers = calloc(1, sizeof(HEADER*));
        list.headers[0] = h;//Set the first pointer to h
        return list;//Return
    }
    else //Handle add to existing list
    {
        //Allocate a pointer for header
        HEADER* h = calloc(1, sizeof(HEADER));
        //Set the Values
        h->key = header.key;
        h->value = header.value;
        //Store the lenght as next index
        int next_index = list.length; //Set the next index to the end of the list.
        list.length++;//Increment the list.
        //Reallocate the headers pointer to pointer to the new size
        list.headers = realloc(list.headers, list.length*sizeof(header));
        //Set the next available index to h.
        list.headers[next_index] = h;
        return list;//Return
    }
}

/**
 * @brief GET_HEADER_BY_INDEX
 * Return the Pointer at a given index in the HEADERS structure.
 * @param list 
 * @param index 
 * @return HEADER* 
 */
HEADER* GET_HEADER_BY_INDEX(HEADERS list, int index)
{
    //If the index is a valid index
    if (index < list.length)
    {
        return list.headers[index];//Return the header pointer
    }
    else//If not return NULL
    {
        return NULL;
    }
}

/**
 * @brief GET_HEADER_BY_KEY
 * Get the header by key of the header
 * @param list 
 * @param key 
 * @return HEADER* 
 */
HEADER* GET_HEADER_BY_KEY(HEADERS list, char* key)
{
    //For the length of the list
    for (int i = 0; i < list.length; i++)
    {
        //Compare the key values
        if (strcmp(list.headers[i]->key,key) == 0)
        {
            //If a match is found return the header.
            return list.headers[i];
        }
    }
    
    //If we make it to this point return NULL as no match was found.
    return NULL;
}