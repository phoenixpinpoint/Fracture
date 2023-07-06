/**
 * @file regex.c
 * @author Adam Guthrie
 * @brief regex.
 * 
 *  Source file to include the entirety of the REGEX Utils module.
 * 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "regex.h"

regex_t regex;//Regex Pattern Buffer
regmatch_t *match_data = 0;//Empty Pointer to store match data.
char* regex_error_message = 0;//Error String for users to check error message.
char* input_buffer = 0;//String to store the last input of parse.


void REGEX_INIT()
{
    match_data = calloc(MAX_MATCH_COUNT, sizeof(regmatch_t)); 
    if(match_data == 0)
    {
        regex_error_message = "Unable to allocate memory\0";
    }
}

void REGEX_PATTERN(char* pattern)
{
    if(regcomp(&regex, pattern, REG_EXTENDED) != 0)
        regex_error_message = "Pattern error\0";
}

void REGEX_PARSE(char* input)
{
    //Copy input into buffer for get_matches
    input_buffer = calloc(strlen(input), sizeof(char));
    strcpy(input_buffer, input);
    
    //Copy input into a temporary buffer to process.
    char* v = calloc(strlen(input), sizeof(char));
    strcpy(v, input);

    //Set the initial offset for rm_so and rm_eo to 0
    int offset = 0;
    for (int i = 0;;i++)//Iterate until break
    {
        int result = REG_NOMATCH;//Default result to REG_NOMATCH (1)
        if (strlen(v) > 0)//If v has a value.
        {
            //Pass the pattern stored in regex, the value in v, MAX_MATCH_COUNT, the current match_data index,
            //into regexec and store the return value in result.
            result = regexec(&regex, v, MAX_MATCH_COUNT, &match_data[i], 0);
        }
        if (result == REG_NOMATCH)//If result is equal to REG_NOMATCH exit
            break;
        if (i == MAX_MATCH_COUNT)//If we have gotten to the MAX_MATCH_COUNT exit
            break;

        //Set v[0] to the end offset of current match
        //Thus removing the match and all charaters before it.
        //Effectinvely trimming the string 
        v += match_data[i].rm_eo;

        //Correct our offsets with position on actual input string.
        //This ensures our location on the actual string value is stored. 
        //No the location on the v string.
        match_data[i].rm_so += offset;
        match_data[i].rm_eo += offset;
        offset = match_data[i].rm_eo;
    }
}

void REGEX_FREE()
{
    free(match_data);
    free(input_buffer);
}

REGEX_MATCHES INITIALIZE_MATCHES(REGEX_MATCHES object)
{
    object.count = 0;
    object.matches = match_data;
    object.strings = 0;
    return object;
}

REGEX_MATCHES GET_MATCHES(REGEX_MATCHES match_struct)
{
    if (match_struct.strings == 0 || match_struct.strings == NULL) //If this is the first Item 
    {
        match_struct.strings = (char**)calloc (1, 1*sizeof(char*));//Initialize the strings array
    }    
    for(int n = 0; n < MAX_MATCH_COUNT; n++)
    {
        //Get the start and end of the last item processed of the array
        //Note: if this is the start it will be 0, because no items have been processed previously
        int start = match_struct.matches[n].rm_so;//get the start of the last item in the array
        int end = match_struct.matches[n].rm_eo;//get the start of the last item in the array
        if (match_struct.strings != 0 && start != -1 && end != -1)
        {
            //Get the string value
            int string_size = 0;
            char* temp = (char*)calloc(1, sizeof(char));
            for (int i = start; i < end; i++)
            {    
                temp = (char*)realloc(temp, string_size+1*sizeof(char));
                temp[string_size] = input_buffer[i];
                string_size++;
            }
            //Null terminate the string
            temp = (char*)realloc(temp, string_size*sizeof(char*));
            temp[string_size] = '\0';
            //Resize The string array and store the value
            int strings_array_size = match_struct.count + 1;
            match_struct.strings = (char**)realloc(match_struct.strings, strings_array_size*sizeof(char*));
            match_struct.strings[match_struct.count] = (char*)calloc(1, strlen(temp)*sizeof(char));
            strcpy(match_struct.strings[match_struct.count], temp);
            match_struct.count++;
            //Free the temp string.
            free(temp);
        }
    }
    return match_struct;
}
