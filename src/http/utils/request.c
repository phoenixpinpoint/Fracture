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
	instance->url[strlen(instance->url)] = '\0';

	instance->body = (char*)malloc(strlen(body)+1*sizeof(char));
	strncpy(instance->body, body, strlen(body)+1);
	instance->body[strlen(instance->body)] = '\0';

	instance->headers = list;
	return instance;
}

/**
 * @brief Set the body object
 * 
 * @param req 
 * @param body 
 */
void SET_REQUEST_BODY(REQUEST* req, char* body)
{
	//Free Old Memory
	if (req->body)
	{
		free(req->body);
		req->body = 0;
	}

	if(body)
    {
        req->body = (char*)malloc(strlen(body)+1*sizeof(char));
        strncpy(req->body, body, strlen(body)+1);
		req->body[strlen(req->body)] = '\0';

    }
}

/**
 * @brief Set the url object
 * 
 * @param req 
 * @param url 
 */
void SET_URL(REQUEST* req, char* url)
{
	//Free Old Memory
	if (req->url)
	{
		free(req->url);
		req->url = 0;
	}

	if(url)
    {
        req->url = (char*)malloc(strlen(url)+1*sizeof(char));
        strncpy(req->url, url, strlen(url)+1);
		req->url[strlen(req->url)] = '\0';
    }
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

	if(req)
	{
		free(req);
	}

	return;
}
