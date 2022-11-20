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

/**
 * @brief REQUEST
 * Request stores representational and acutal data that will be submitted to the cURL
 * lib call.
 */
//typedef struct REQUEST REQUEST;

/**
 * @brief REQUEST
 * Request stores representational and acutal data that will be submitted to the cURL
 * lib call.
 */
typedef struct REQUEST {
    char* url;      // URL of the endpoint
    char* body;     // Raw body as char array TODO: build JSON body
    char* header;  // String representation of header.
} REQUEST;

#endif