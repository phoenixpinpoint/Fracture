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

void RENDER_PAGE(char* pagePath)
{
    //Load the page into memory
    char* page = READ_FILE(pagePath);
    
    //Load and Render the layout
    char* layout;
    REGEX_MATCHES pageLayout = BK_PARSE_FILE(page, "@layout (.*?);");

    if(pageLayout.count > 1 && pageLayout.count < MAX_MATCH_COUNT)
    {
        char* layoutName = pageLayout.strings[1];
        char* layoutPath = (char*)malloc(strlen("assets/")+strlen(layoutName));
        strcpy(layoutPath, "assets/");
        strncat(layoutPath, layoutName, strlen("assets/")+strlen(layoutName)+1);
        layoutPath[strlen(layoutName)+strlen("assets/")]='\0';
        layout = READ_FILE(layoutPath);
        free(layoutPath);
    }
    else
    {
        return;
    }

    REGEX_MATCHES head = BK_PARSE_FILE(layout, "@head\n(.*?)\n@headclose");
    if(head.count > 1 && head.count < MAX_MATCH_COUNT)
    {
        SET_HEAD_INNER_HTML(head.strings[1]);
    }

    REGEX_MATCHES body = BK_PARSE_FILE(layout,"@body\n(.*?)\n@bodyclose");
    
    if(body.count > 1 && body.count < MAX_MATCH_COUNT)
    {
        SET_BODY_INNER_HTML(body.strings[1]);
    }

    // Load and render the rest of the page.
    head = BK_PARSE_FILE(page, "@head\n(.*?)\n@headclose");
    if(head.count > 1 && head.count < MAX_MATCH_COUNT)
    {
        SET_HEAD_INNER_HTML(head.strings[1]);
    }

    body = BK_PARSE_FILE(page,"@body\n(.*?)\n@bodyclose");
    if(body.count > 1 && body.count < MAX_MATCH_COUNT)
    {
        SET_BODY_INNER_HTML(body.strings[1]);
    }
}

EM_JS(void, ADD_SCRIPT_TO_HEAD, (char* script), {
    var newScript = document.createElement("script");
    newScript.type 
            = 'text/javascript';
    var inlineScript = document.createTextNode(UTF8ToString(script));
    newScript.appendChild(inlineScript); 
    document.head.appendChild(newScript);
    return;
});

void ADD_SCRIPTS()
{
    //Get all scripts in assets/scripts
    DIRECTORYLIST *scripts = LIST_FILES("assets/scripts");
    
    //For each script file.
    for (int iteration = 0; iteration < scripts->length; iteration++)
    {
        //Store the file name and allocate a string for the path
        char* scriptFileName = scripts->directories[iteration]->d_name;
        char* scriptPath = calloc(strlen("assets/scripts/")+strlen(scriptFileName), sizeof(char));
        
        //append "assets/scripts" and the directory name
        strncat(scriptPath, "assets/scripts/", strlen("assets/scripts/"));
        strncat(scriptPath, scriptFileName, strlen("assets/scripts/") + strlen(scriptFileName));

        //Load the file into a buffer and add the script to the document head.
        char* scriptInstance = READ_FILE(scriptPath);
        ADD_SCRIPT_TO_HEAD(scriptInstance);

        //Clean up the buffers
        free(scriptInstance);
        free(scriptPath);
    }
}