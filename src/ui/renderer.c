/**
 * @file renderer.c
 * @author Adam C. Guthrie
 * @brief renderer.c
 * 
 *  Renderer loads assets in the system and renders based on the DOMS
 * 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 */
#include "renderer.h"

EM_JS(void, SET_INNER_HTML_BY_ID, (char* id, char* body), {
    document.getElementById(UTF8ToString(id)).innerHTML = UTF8ToString(body);
    return;
});

EM_JS(void, SET_BODY_INNER_HTML, (char* body), {
    document.body.innerHTML = UTF8ToString(body);
    return;
});

EM_JS(void, SET_HEAD_INNER_HTML, (char* body), {
    document.head.innerHTML = UTF8ToString(body);
    return;
});

DIRECTORYLIST* GET_ASSET_FILES()
{
    DIRECTORYLIST* assets = LIST_FILES("/assets");
    return assets;
}

void RENDER()
{
    //DIRECTORYLIST* assets = GET_ASSET_FILES();
    char* layout = READ_FILE("assets/layouts/layout.bk.html");
    REGEX_MATCHES head = BK_PARSE_FILE(layout, "@head\n(.*?)\n@headclose");
    if(head.count > 1)
    {
        SET_HEAD_INNER_HTML(head.strings[1]);
    }

    REGEX_MATCHES body = BK_PARSE_FILE(layout,"@body\n(.*?)\n@bodyclose");
    if(body.count > 1)
    {
        SET_BODY_INNER_HTML(body.strings[1]);
    }
}