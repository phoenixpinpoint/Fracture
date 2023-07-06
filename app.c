
#include "src/webc.h"
#include <emscripten.h>

int main()
{
    printf("Loading Site\n");
    char* page = READ_FILE("assets/default.html");

    SET_BODY_INNER_HTML(page);
    return 0;
}