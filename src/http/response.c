/**
 * @file response.c
 * @author Adam C. Guthrie
 * @brief response.c
 * 
 *  Response containerizes the response data as a wrapper.
 * 
 * @version 0.1
 * @date 2022-11-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "response.h"

/**
 * @brief Create a response object
 * 
 * @param response_code 
 * @param body 
 * @param list 
 * @return RESPONSE* 
 */
RESPONSE* CREATE_RESPONSE(long response_code, char* body, HEADERLIST* list)
{
    RESPONSE *instance = (RESPONSE*)malloc(sizeof(RESPONSE));

	instance->response_code = 0;

	instance->body = (char*)malloc(strlen(body)+1*sizeof(char));
	strncpy(instance->body, body, strlen(body)+1);
    instance->body[strlen(body)] = '\0';

	instance->headers = list;
	return instance;
}

/**
 * @brief Frees a response object
 * 
 * @param res 
 */
void FREE_RESPONSE(RESPONSE* res)
{
    if (res->body)
    {
        free(res->body);
    }

    if(res)
    {
        free(res);
    }
}

/**
 * @brief Set the body object
 * 
 * @param res 
 * @param body 
 */
void SET_RESPONSE_BODY(RESPONSE* res, char* body)
{
    	//Free Old Memory
	if (res->body)
	{
		free(res->body);
		res->body = 0;
	}

	if(body)
    {
        res->body = (char*)malloc(strlen(body)+1*sizeof(char));
        strncpy(res->body, body, strlen(body)+1);
		res->body[strlen(res->body)] = '\0';

    }
}