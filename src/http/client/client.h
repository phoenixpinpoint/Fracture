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

#endif