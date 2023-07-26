
#include "src/webc.h"
#include "deps/parson/parson.c"
#include <emscripten.h>

void quote()
{
    REQUEST *req = CREATE_REQUEST("https://ron-swanson-quotes.herokuapp.com/v2/quotes","",0);
    RESPONSE *res = GET(req);

    buffer_t *quoteBuffer = buffer_new_with_string(res->body);

    JSON_Value *quoteRoot;
    quoteRoot = json_parse_string(quoteBuffer->data);
    int quoteParseResultCode = json_value_get_type(quoteRoot);
    if(quoteParseResultCode == 5)
    {
        JSON_Array *quoteBodyArray = json_value_get_array(quoteRoot);
        printf("%s\n", quoteBodyArray->items[0]->value.string.chars);
        buffer_free(quoteBuffer);
        quoteBuffer = buffer_new_with_string(quoteBodyArray->items[0]->value.string.chars);
        buffer_append(quoteBuffer, " - Ron Swanson\0");
        SET_INNER_HTML_BY_ID("quote", quoteBuffer->data);
    }
    else {
        printf("failed to parse quote response.\n");
    }

    FREE_REQUEST(req);
    FREE_RESPONSE(res);
    buffer_free(quoteBuffer);
    json_value_free(quoteBuffer);
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