#include "../utils/regex.h"

// typedef struct BK_TAG {
//     char* type;
//     char* contents;
// } BK_TAG;

// BK_TAG* CREATE_TAG(char* type, char* contents);

REGEX_MATCHES BK_PARSE_FILE(char* fileBuffer, char* pattern);