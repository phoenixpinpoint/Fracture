/**
 * @file headers.c
 * @author Adam Guthrie
 * @brief headers.h
 * 
 *  Headers stores a struct template for keeping headers in both requests and responses.
 * 
 * @version 0.1
 * @date 2022-11-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "headers.h"

/**
 * @brief CREATE_HEADER
 * CREATE_HEADER takes two string array literals and returns a pointer to a newly created
 * header object.
 * @return HEADER *
 */
HEADER* CREATE_HEADER(char* key, char* value)
{
    //Create an instance pointer.
    HEADER *instance = (HEADER*)malloc(sizeof(HEADER));

    //Allocate Memory for Key Value and Copy String
    if (key)
    {
        instance->key = (char*)malloc(strlen(key)*sizeof(char));
        strncpy(instance->key, key, strlen(key));
    }
    else {
        instance->key = 0;
    }

    if(value)
    {
        instance->value = (char*)malloc(strlen(value)*sizeof(char));
        strncpy(instance->value, value, strlen(value));
    }
    else {
        instance->value = 0;
    }

    //Return the Resulting Pointer
    return instance;
}

/**
 * @brief FREE_HEADER
 * FREE_HEADER frees the the header struct an values
 * @param h 
 */
void FREE_HEADER(HEADER* h)
{
    if(h->key)
    {
        free(h->key);
    }
    if(h->value)
    {
        free(h->value);
    }
    if(h)
    {
        free(h);
    }
    return;
}

/**
 * @brief Set the key object
 * 
 * @param h 
 * @param key 
 */
void SET_KEY(HEADER *h, char* key)
{
    // If there is key value free it.
    if(h->key)
    {
        free(h->key);
        h->key = 0;
    }
    
    //If there is a key value
    if(key)
    {
        h->key = (char*)malloc(strlen(key)*sizeof(char));
        strncpy(h->key, key, strlen(key));
    }
    return;
}

/**
 * @brief Set the value object
 * 
 * @param h 
 * @param value 
 */
void SET_VALUE(HEADER *h, char* value)
{
    //If there is a value string free it
    if(h->value)
    {
        free(h->value);
        h->value = 0;
    }

    //Value passed to the function
    if(value)
    {
        h->value = (char*)malloc(strlen(value)*sizeof(char));
        strncpy(h->value, value, strlen(value));
    }
}