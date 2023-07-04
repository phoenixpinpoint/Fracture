/**
 * @file request.c
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
#include "request.h"

/**
 * @brief CREATE_REQUET
 * Request object takes a url, body and HEADERLIST object.
 * @returns REQUEST*
 */
REQUEST* CREATE_REQUEST(char* url, char* body, HEADERLIST* list)
{
	REQUEST *instance = (REQUEST*)malloc(sizeof(REQUEST));

	instance->url = (char*)malloc(strlen(url)+1*sizeof(char));
	strncpy(instance->url, url, strlen(url)+1);

	instance->body = (char*)malloc(strlen(body)+1*sizeof(char));
	strncpy(instance->body, body, strlen(body)+1);

	instance->headers = list;
	return instance;
}

/**
 * @brief FREE_REQUEST
 * Free the request object.
 */
void FREE_REQUEST(REQUEST* req)
{
	if(req->url)
	{
		free(req->url);
	}

	if(req->body)
	{
		free(req->body);
	}

	return;
}
