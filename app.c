
#include "src/webc.h"
#include <emscripten.h>

int main()
{
    printf("Loading Assets\n");
    DIRECTORYLIST* assets = GET_ASSET_FILES();
    char* layout = READ_FILE("assets/layouts/layout.bk.html");
    printf("Rendering Site\n");
    RENDER();
    return 0;
}