
#include "src/webc.h"
#include <emscripten.h>

void quote()
{
    REQUEST *req = CREATE_REQUEST("https://ron-swanson-quotes.herokuapp.com/v2/quotes","",0);
    RESPONSE *res = GET(req);

    buffer_t *quoteBuffer = buffer_new_with_string(res->body);
    buffer_append(quoteBuffer, " - Ron Swanson\0");

    SET_INNER_HTML_BY_ID("quote", quoteBuffer->data);
    
    FREE_REQUEST(req);
    FREE_RESPONSE(res);
    buffer_free(quoteBuffer);
}

int main()
{
    printf("Rendering home Page\n");
    wc_render_page("assets/pages/home.bk.html");

    printf("Loading Scripts\n");
    //ADD_SCRIPTS();

    quote();

    return 0;
}