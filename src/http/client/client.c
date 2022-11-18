/**
 * @file client.c
 * @author Adam Guthrie
 * @brief client.c
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <curl/curl.h>

#include "client.h"

// Setup Client cURL.
CURL *curl;

/**
 * @brief HTTP_CLIENT_INIT
 * HTTP_CLIENT_INIT setups the cURL globally. With cURL defaults.
 */
void HTTP_CLIENT_INIT()
{
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
}

/**
 * @brief HTTP_CLIENT_CLEANUP
 * HTTP_CLIENT_CLEANUP calls curl_global_cleanup to properly handle the closure of the cURL lib.
 */
void HTTP_CLIENT_CLEANUP()
{
  curl_global_cleanup();
}

/**
 * @brief HTTP_CLIENT_VALID
 * HTTP_CLIENT_VALID returns true or false if curl is set. 
 * @return bool - Flag for HTTP client validity
 */
bool HTTP_CLIENT_VALID()
{
  if(curl)
  {
    return true;
  }
  else {
    return false;
  }
}
