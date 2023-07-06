/**
 * @file regexer.h
 * @author Adam Guthrie
 * @brief regex.h
 * 
 *  Header file to include the entirety of the REGEX Utils module.
 * 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef REGEX_H
#define REGEX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCH_COUNT 256

typedef struct REGEX_MATCHES
{
    int count;//Count of matches on regmatch_t
    regmatch_t* matches;//regmatch_t array pointer
    char** strings;//Array of strings with the matched string.
} REGEX_MATCHES;


void REGEX_INIT();

void REGEX_PATTERN(char* pattern);

void REGEX_PARSE(char* input);

void REGEX_FREE();

REGEX_MATCHES INITIALIZE_MATCHES(REGEX_MATCHES object);

REGEX_MATCHES GET_MATCHES(REGEX_MATCHES match_struct);


#endif