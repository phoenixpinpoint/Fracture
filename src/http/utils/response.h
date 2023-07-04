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
    int response_code;  // Response Code
    char* body;         // Raw body as char array TODO: build JSON body
    HEADERLIST* headers;       // String representation of header.
} RESPONSE;

/**
 * @brief Create a response object
 * 
 * @param response_code 
 * @param body 
 * @param list 
 * @return RESPONSE* 
 */
RESPONSE* CREATE_RESPONSE(long response_code, char* body, HEADERLIST* list);

/**
 * @brief Frees a response object
 * 
 * @param res 
 */
void FREE_RESPONSE(RESPONSE* res);

/**
 * @brief Set the body object
 * 
 * @param res 
 * @param body 
 */
void SET_RESPONSE_BODY(RESPONSE* res, char* body);

#endif