/**
 * @file client.h
 * @author Adam Guthrie
 * @brief client.h
 * 
 *  HTTP Client logical code. This client is a wrapper around the libcurl cURL library.
 *  Currently in scope is GET, POST, PATCH, DELETE.
 * 
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CLIENT_H
#define CLIENT_H

#include "../utils/utils.h"
#include <stdbool.h>

/**
 * @brief HTTP_CLIENT_INIT()
 * HTTP_CLIENT_INIT() setups the cURL globally. With cURL defaults.
 */
void HTTP_CLIENT_INIT();

/**
 * @brief HTTP_cleanup
 * HTTP_cleanup calls curl_global_cleanup to properly handle the closure of the cURL lib.
 */
void HTTP_CLIENT_CLEANUP();

/**
 * @brief HTTP_valid
 * HTTP_valid returns true or false if curl is set. 
 */
bool HTTP_CLIENT_VALID();

/**
 * @brief HTTP_ALLOW_REDIRECTS 
 * HTTP_ALLOW_REDIRECTS is a function to enable/disable redirection.
 */
void HTTP_ALLOW_REDIRECTS(bool);

/**
 * @brief HTTP_SET_MAX_REDIRECTS
 * HTTP_SET_MAX_REDIRECTS sets the maximum number of times a redirect is called.
 */
void HTTP_SET_MAX_REDIRECTS(int);

/**
 * @brief HTTP_GET_MAX_REDIRECTS
 * HTTP_GET_MAX_REDIRECTS returns the current maximum allowed redirects. Default: 100.
 * @return int 
 */
int HTTP_GET_MAX_REDIRECTS();

/**
 * @brief GET
 * GET calls the cURL lib with a REQUEST structure and returns a RESPONSE structure
 * @return RESPONSE 
 */
RESPONSE GET(REQUEST);

#endif