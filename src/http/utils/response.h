/**
 * @file response.h
 * @author Adam C. Guthrie
 * @brief response.h
 * 
 *  Response containerizes the response data as a wrapper.
 * 
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef RESPONSE_H
#define RESPONSE_H

#include "./headers.h"

typedef struct RESPONSE {
    long response_code;  // Response Code
    char* body;         // Raw body as char array TODO: build JSON body
    HEADERS* headers;   // Pointer to a HEADER.
} RESPONSE;

#endif