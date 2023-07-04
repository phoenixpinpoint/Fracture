/**
 * @file headers.h
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
#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief HEADER
 * HEADER is a structure that stores the key value pair of a given
 * HTTP header.
 * It contains a string key for the key. As well as a void pointer to store whatever
 * value is returnd.
 */
typedef struct HEADER {
    char* key;
    char* value;
} HEADER;

/**
 * @brief HEADERLIST
 * HEADERLIST is a structure that stores length which is the number of headers in the list.
 * As well as an "array" of pointers that are the headers.
 */
typedef struct HEADERLIST {
    int length;
    HEADER** headers;
} HEADERLIST;


/**
 * @brief CREATE_HEADER
 * CREATE_HEADER returns a pointer to a newly created header object.
 * @return HEADER *
 */
HEADER* CREATE_HEADER(char* key, char* value);

/**
 * @brief FREE_HEADER
 * FREE_HEADER frees the the header struct an values
 * @param h 
 */
void FREE_HEADER(HEADER* h);

/**
 * @brief Set the key object
 * 
 * @param h 
 * @param key 
 */
void SET_KEY(HEADER *h, char* key);

/**
 * @brief Set the value object
 * 
 * @param h 
 * @param value 
 */
void SET_VALUE(HEADER *h, char* value);

/**
 * @brief Create a header list object
 * 
 * @return HEADERLIST* 
 */
HEADERLIST* CREATE_HEADER_LIST();

/**
 * @brief Add Header to Existing List of Headers
 * 
 * @param list 
 * @param header 
 */
void ADD_HEADER(HEADERLIST *list, HEADER *header);

/**
 * @brief Get the header object
 * 
 * @param list 
 * @param index 
 * @return HEADER* 
 */
HEADER* GET_HEADER(HEADERLIST *list, int index);

/**
 * @brief Get the header by key object
 * 
 * @param list 
 * @param key 
 * @return HEADER* 
 */
HEADER* GET_HEADER_BY_KEY(HEADERLIST *list, char* key);

/**
 * @brief removes header at a given index
 * 
 * @param list 
 * @param index 
 */
void REMOVE_HEADER(HEADERLIST *list, int index);

/**
 * @brief removes header at a given key
 * 
 * @param list 
 * @param key 
 */
void REMOVE_HEADER_BY_KEY(HEADERLIST *list, char* key);

/**
 * @brief Get the header object index
 * 
 * @param list 
 * @param key 
 * @return int 
 */
int GET_HEADER_INDEX(HEADERLIST *list, char* key);

/**
 * @brief Prints out the Header List
 * 
 * @param list 
 */
void PRINT_HEADER_LIST(HEADERLIST *list);

/**
 * @brief Frees the Header list structure
 * NOTE: does not free the HEADERs themselves.
 * @param list 
 */
void FREE_HEADER_LIST(HEADERLIST *list);

#endif