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

bool ALLOW_REDIRECTS = true;

static size_t header_callback(char *buffer, size_t size,size_t nitems, void *userdata)
{
  /* received header is nitems * size long in 'buffer' NOT ZERO TERMINATED */
  /* 'userdata' is set with CURLOPT_HEADERDATA */
  printf("Buffer: %s**\n", buffer);
  printf("size: %d\n", size);
  printf("nitems: %d\n", nitems);
  //printf("Userdata: %s\n", userdata);
  size_t numbytes = size * nitems;
  //printf("%.*s\n", numbytes, buffer);
  printf("numbytes: %d\n", numbytes);
  return nitems * size;
}

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

/**
 * @brief HTTP_ALLOW_REDIRECTS 
 * HTTP_ALLOW_REDIRECTS is a function to enable/disable redirection.
 * @param value 
 */
void HTTP_ALLOW_REDIRECTS(bool value)
{
  ALLOW_REDIRECTS = value;
}

/**
 * @brief GET
 * GET calls the cURL lib with a REQUEST structure and returns a RESPONSE structure
 * @return RESPONSE 
 */
RESPONSE GET(REQUEST req)
{
  RESPONSE res;
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, req.url);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    CURLcode curl_res;
    curl_res = curl_easy_perform(curl);
    if(curl_res != CURLE_OK)
    {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_res));
    }
    else
    {
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
      res.response_code = response_code;
    }
    return res;
  }
  else
  {
    return res;
  }
}