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
    void* value;
} HEADER;

/**
 * @brief HEADERS
 * HEADERS is a structure that stores length which is the number of headers in the list.
 * As well as an "array" of pointers that are the headers.
 */
typedef struct HEADERS {
    int length;
    HEADER** headers;
} HEADERS;

/**
 * @brief ADD_HEADERS
 * ADD_HEADERS takes a HEADERS list and a HEADER and adds the HEADER to HEADERS. 
 * If there isn't any current headers it allocates memory for the user. 
 * IF there is it reallocates and adds the header.
 * @return HEADERS 
 */
HEADERS ADD_HEADER(HEADERS, HEADER);

/**
 * @brief GET_HEADER_BY_INDEX
 * Return the Pointer at a given index in the HEADERS structure.
 * @return HEADER* 
 */
HEADER* GET_HEADER_BY_INDEX(HEADERS, int);

/**
 * @brief GET_HEADER_BY_KEY
 * Get the header by key of the header
 * @return HEADER* 
 */
HEADER* GET_HEADER_BY_KEY(HEADERS, char*);

#endif