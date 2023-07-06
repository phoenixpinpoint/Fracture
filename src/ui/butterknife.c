#include "butterknife.h"

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