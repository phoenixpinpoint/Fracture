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
int MAX_REDIRECT = 100;

int bodyInit = 0;
char* bodyTextGobalVar;

/**
 * @brief header_callback
 * 
 *  header_callback is the callback function for the libcurl HEADERFUNCTION option. 
 * 
 * @param buffer - CHAR* Raw header string.
 * @param size - The size of the items.
 * @param nitems - The number of the items.
 * @param userdata - By default this is a void*, in this library userdata is
 * a pointer to a HEADERS* struct.
 * @return size_t 
 */
static size_t headerCallback(char *buffer, size_t size, size_t nitems, void *userdata)
{
  /*
   * Generally, this function copies the buffer into bufferCopy in order to
   * perserve the original raw data to be attached to the HEADER struct.
   * 
   * Then use strtok to break the raw header into key value pairs if 
   * the header is valid.
   * 
   * As noted below strtok appears to return the original string if there is 
   * no match. I am currently investigating this in order to ensure what
   * I am expiriencing is not undefined behavour. Regardless since it returns
   * the original buffer if no match, we check the return value (key) against
   * the original buffer to see if a match was found as a match would be 
   * shorter the the buffer.
   * 
   * If match is found we call strtok again to get the remainder of the
   * buffer which becomes the value. Since the value has a prepended space
   * we remove that space. 
   */

  //Copy the buffer into a copy. 
  char* bufferCopy = (char*)calloc(nitems, sizeof(char));
  strncpy(bufferCopy, buffer, nitems);

  //Split the header string on the first ":".
  char* key = strtok(buffer, ":");

  //I was under the impression that strtok returns NULL without a match
  //It appears to return the buffer instead....therefore we are doing a 
  //basic strncmp.

  //Compare the original buffer and the key
  //If the key is less than the bufferCopy a match is found. 
  if (strncmp(key, bufferCopy, nitems) <  0)
  {
    //Call strtok again with no string to match for. This returns the
    //Remaining string in the buffer.
    char* value = strtok(NULL, "");

    //If the first value is a space, remove it.
    if (value[0] == ' ') value++;

    //Add the header
    HEADER *header = CREATE_HEADER(key, value);
    ADD_HEADER(userdata, header);
  }

  free(bufferCopy);

  return nitems * size;
}

static size_t bodyCallback(char *data, size_t size, size_t nitems, void *userdata)
{
  /**
   * Generally this function is called 1-X number of times. On the initial call it
   * allocates the bodyTextGlobalVar and copies the buffer to the global variable. It 
   * then sets the bodyInit flag to 1 which means the next call will reallocate the
   * string and concatenate the string with the new buffer data.
   */
  if(bodyInit == 0)
  {
    bodyTextGobalVar = (char*)calloc(nitems+1, sizeof(char));
    strncpy(bodyTextGobalVar, data, nitems+1);
    bodyTextGobalVar[nitems] = '\0';
    bodyInit = 1;
  }
  else
  {
    size_t oldBodySize = strlen(bodyTextGobalVar);
    bodyTextGobalVar = realloc(bodyTextGobalVar, oldBodySize+nitems+1);
    strncat(bodyTextGobalVar, data, nitems);
    bodyTextGobalVar[oldBodySize+nitems] = '\0';
  }
  
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
 * @brief HTTP_SET_MAX_REDIRECTS
 * HTTP_SET_MAX_REDIRECTS sets the maximum number of times a redirect is called.
 * @param max 
 */
void HTTP_SET_MAX_REDIRECTS(int max)
{
  MAX_REDIRECT = max;
}


/**
 * @brief HTTP_GET_MAX_REDIRECTS()
 * HTTP_GET_MAX_REDIRECTS returns the current maximum allowed redirects. Default: 100.
 * @return int 
 */
int HTTP_GET_MAX_REDIRECTS()
{
  return MAX_REDIRECT;
}

/**
 * @brief GET
 * GET calls the cURL lib with a REQUEST structure and returns a RESPONSE structure
 * @return RESPONSE 
 */
RESPONSE* GET(REQUEST* req)
{
  //Create A Response Object
  RESPONSE *res = CREATE_RESPONSE(0, "", 0);

  //Allocate and initialize the Headers Struct
  res->headers = calloc(1, sizeof(HEADERLIST));
  res->headers->length = 0;
  res->headers->headers = 0;

  //If curl is valid
  if(curl)
  {
    //Setup cURL
    curl_easy_setopt(curl, CURLOPT_URL, req->url); //Set the URL
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, res->headers);//Set the Header Struct.
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);//Set the HEADERFUNCTION
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, bodyCallback);//Set our WRITEFUNCTION
    CURLcode curl_res;//Create a response object.

  curl_res = curl_easy_perform(curl);//Execute the cURL call.
    
    if(curl_res != CURLE_OK)
    {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curl_res));
      return res;
    }
    else
    {
      //Setup response code handling.
      long response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
      res->response_code = response_code;
      //IF we get a moved HTTP code and redirects are enabled.
      if(response_code == 301 && ALLOW_REDIRECTS == true)
      {
        //Get the location header from the Response
        size_t lengthOfLocation = strlen(GET_HEADER_BY_KEY(res->headers, "location")->value);
        char* redirectUrlValue = (char*)malloc(lengthOfLocation+1*sizeof(char));
        strncpy(redirectUrlValue, GET_HEADER_BY_KEY(res->headers, "location")->value, lengthOfLocation+1*sizeof(char));
        redirectUrlValue[strlen(redirectUrlValue)] = '\0';

        //Scrub /r and /n from URL
        for(int iteration = 0; iteration < strlen(redirectUrlValue); iteration++)
        {
          if(redirectUrlValue[iteration] == '\r' || redirectUrlValue[iteration] == '\n')
          {
            redirectUrlValue[iteration] = '\0';
          }        
        }

        for (int header = 0; header < res->headers->length; header++)
        {
          FREE_HEADER(res->headers->headers[header]);
        }

        
        //Set the redirect URL and free the temporary var.
        SET_URL(req, redirectUrlValue);
        free(redirectUrlValue);

        //Call GET again with the new request.
        return res = GET(req);
      }
      //Set the body
      SET_RESPONSE_BODY(res, bodyTextGobalVar);
      free(bodyTextGobalVar);
      bodyInit = 0;
    }
    //Return Response.
    return res;
  }
  else
  {
    return res;
  }
}
