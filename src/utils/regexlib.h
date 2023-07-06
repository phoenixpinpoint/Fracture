/***********************************************************************
* FILENAME :        regexlib.h
*
* DESCRIPTION : Generic Regex Wrapper for regex.h
*
*
* FUNCTIONS :
*   void regex_init(); //Initializes the wrapper library.
*   void regex_pattern(char* pattern); //Defines the regex pattern to use.
*   void regex_parse(char* input); //Reads through the input and checks it against the pattern.
*   void regex_free(); //Call when finished to free dynamic memory.
*   regex_matches initialize_matches(regex_matches object); //Initializes a regex_matches struct to store results
*   regex_matches get_matches(regex_matches match_struct); //takes the regmatch_t and breaks into strings with a count value.
*
* NOTES :
*   How to Use:
*       Add #include "regexlib.h" to your source file.
*       Call regex_init()
*       Call regex_pattern(<some char pointer>) with a char* buffer containing the pattern string
*       Call regex_parse(<some input string>) with a char* buffer containing the input string
*       Define a regex_matches local.
*       Call initialize_matches(<your local>) on your local regex_matches
*       Call get_matches(<>)
**/

/**
 * \file regexlib.h
 * Creates server socket interface.
 * 
 *Generic Regex Wrapper for regex.h
 */

//#include <>s
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

//#include ""s

//#defines
#define MAX_MATCH_COUNT 256

//Data Types/Structs
struct regex_matches 
{
    int count;//Count of matches on regmatch_t
    regmatch_t* matches;//regmatch_t array pointer
    char** strings;//Array of strings with the matched string.
} typedef regex_matches;

//Global Integral Constants

//Global Variables
regex_t regex;//Regex Pattern Buffer
regmatch_t *match_data = 0;//Empty Pointer to store match data.
char* regex_error_message = 0;//Error String for users to check error message.
char* input_buffer = 0;//String to store the last input of parse.

//Function Prototypes
void regex_init();
void regex_pattern(char* pattern);
void regex_parse(char* input);
void regex_free();
regex_matches initialize_matches(regex_matches object);
regex_matches get_matches(regex_matches match_struct);


/**
 * @fn regex_init()
 * Initializes the wrapper library
 * 
 * Allocates an array pointer for regmatch_t, the size of MAX_MATCH_COUNT (256 by default).
 * Checks to see if match_data was allocated.
 * If it was not set regex_error_message to indicate allocate failure.
 */
void regex_init()
{
    match_data = calloc(MAX_MATCH_COUNT, sizeof(regmatch_t)); 
    if(match_data == 0)
    {
        regex_error_message = "Unable to allocate memory\0";
    }
}

/**
 * @fn regex_pattern(char* pattern)
 * Defines the regex pattern to use.
 * 
 * Runs regcomp with the regmatch_t arrya pointer and the regex_t value.
 * This is set to REG_EXTENDED by default. 
 * If regcomp doesn't succed (return 0) set regex_error_message to Pattern error.
 * 
 * @param pattern The pattern string.
 */
void regex_pattern(char* pattern)
{
    if(regcomp(&regex, pattern, REG_EXTENDED) != 0)
        regex_error_message = "Pattern error\0";
}

/**
 * @fn regex_parse(char* input)
 * Reads through the input and checks it against the pattern.
 * 
 * Stores the input value in a input_buffer value for later use.
 * Copies the input value to a temp string
 * Iterates until regexec returns REG_NOMATCH and stores the data
 * in match_data regmatch_t array.
 * 
 * @param input The string parse against the pattern string.
 */
void regex_parse(char* input)
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

/**
 * @fn regex_free
 * Call when finished to free dynamic memory.
 * 
 * This function frees malloc'd, calloc'd and realloc'd values.
 *
 * Note: regex_error_message is a pointer, but is not dynamically allocated,
 * thus it shall not free()'d.
 */
void regex_free()
{
    free(match_data);
    free(input_buffer);
}

/**
 * @fn initialize_matches
 * Initializes a regex_matches struct to store results
 * 
 * Takes a local regex_matches object and sets the defaults values

 * Note: If you create multiple regex_matches structs they will share the same 
 * match_data pointer. 
 * 
 * @param object local regex_matches to initialize
 *
 * @return will allways be the passed local. 
 */
regex_matches initialize_matches(regex_matches object)
{
    object.count = 0;
    object.matches = match_data;
    object.strings = 0;
    return object;
}

/**
 * @fn get_matches
 * Takes the regmatch_t and breaks into strings with a count value.
 * 
 * This function takes a regex_matches structure and populates it.
 * 
 * @param match_struct local regex_matches to initialize
 *
 * @return will allways be the passed local. 
 */
regex_matches get_matches(regex_matches match_struct)
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