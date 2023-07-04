/**
 * @file request.h
 * @author Adam Guthrie
 * @brief 
 * 
 *  Request is module that wraps cURL request into a better interface for the user.
 * 
 * @version 0.1
 * @date 2022-11-18
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef REQUEST_H
#define REQUEST_H

#include "./headers.h"

/**
 * @brief REQUEST
 * Request stores representational and acutal data that will be submitted to the cURL
 * lib call.
 */
typedef struct REQUEST {
    char* url;          // URL of the endpoint
    char* body;         // Raw body as char array TODO: build JSON body
    HEADERLIST* headers;  // Request headers
} REQUEST;

/**
 * @brief CREATE_REQUET
 * Request object takes a url, body and HEADERLIST object.
 * @returns REQUEST*
 */
REQUEST* CREATE_REQUEST(char* url, char* body, HEADERLIST* list);

/**
 * @brief FREE_REQUEST
 * Free the request object.
 */
void FREE_REQUEST(REQUEST* req);

/**
 * @brief Set the body object
 * 
 * @param req 
 * @param body 
 */
void SET_REQUEST_BODY(REQUEST* req, char* body);

/**
 * @brief Set the url object
 * 
 * @param req 
 * @param url 
 */
void SET_URL(REQUEST* req, char* url);

#endif
