
#include "src/webc.h"
#include <emscripten.h>

void quote()
{
    REQUEST *req = CREATE_REQUEST("https://ron-swanson-quotes.herokuapp.com/v2/quotes","",0);
    RESPONSE *res = GET(req);
    SET_INNER_HTML_BY_ID("quoteResponse", res->body);
    FREE_REQUEST(req);
    FREE_RESPONSE(res);
}

int main()
{
    printf("Loading Asset Files\n");
    DIRECTORYLIST* assets = GET_ASSET_FILES();

    printf("Rendering home Page\n");
    RENDER_PAGE("assets/pages/home.bk.html");

    printf("Loading Scripts\n");
    ADD_SCRIPTS();

    return 0;
}