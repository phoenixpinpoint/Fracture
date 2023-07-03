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

#endif