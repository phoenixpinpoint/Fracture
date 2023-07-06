#include "butterknife.h"


// BK_TAG* CREATE_TAG(char* type, char* contents)
// {
//     BK_TAG *tag = (BK_TAG*)malloc(sizeof(BK_TAG));

//     //If type is a valid value
//     if (strlen(type) > 0)
//     {
//         tag->type = (char*)malloc(strlen(type)+1*sizeof(char));
//         strncpy(tag->type, type, strlen(type)+1);
//         tag->type[strlen(tag->type)] = '\0';
//     }
//     else {
//         return (BK_TAG*)-1;
//     }

//     //If contents is a valid value
//     if (strlen(contents) > 0)
//     {
//         tag->contents = (char*)malloc(strlen(contents)+1*sizeof(char));
//         strncpy(tag->contents, contents, strlen(contents)+1);
//         tag->contents[strlen(tag->contents)] = '\0';
//     }
//     else {
//         return (BK_TAG*)-1;
//     }
//     return tag;
// }

REGEX_MATCHES BK_PARSE_FILE(char* fileBuffer, char* pattern)
{
    REGEX_INIT();

    REGEX_PATTERN(pattern);

    REGEX_PARSE(fileBuffer);

    REGEX_MATCHES matches;
    matches = INITIALIZE_MATCHES(matches);
    matches = GET_MATCHES(matches);
    REGEX_FREE();

    return matches;
}


    // REGEX_INIT();

    // REGEX_PATTERN("Hello");