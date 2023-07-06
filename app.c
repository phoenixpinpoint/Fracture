
#include "src/webc.h"
#include <emscripten.h>

int main()
{
    printf("Loading Assets\n");
    DIRECTORYLIST* assets = GET_ASSET_FILES();
    char* head = READ_FILE("assets/layouts/head.html");
    char* page = READ_FILE("assets/layouts/default.html");
    printf("Loading Site\n");
    SET_HEAD_INNER_HTML(head);
    SET_BODY_INNER_HTML(page);
    return 0;
}