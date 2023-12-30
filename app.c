/*
* app.c
* This is the start a great thing.
*/

#include <fracture.c>
#include "survey.c"

//In this simple function we call the Ron Swanson API
buffer_t* quote()
{
    //Create a buffer to store our quote text.
    buffer_t *quoteBuffer;

    //Build our HTTP request with the URL, NULL Headers, NULL Body
    HTTP_REQUEST *req = CREATE_HTTP_REQUEST("https://ron-swanson-quotes.herokuapp.com/v2/quotes",NULL,NULL);
    HTTP_RESPONSE *res = HTTP_GET(req);//Call our HTTP_GET function.

    //Check the response code
    if(res->response_code == 200)
    {
      //Store the quote string
      quoteBuffer = buffer_new_with_string(res->body);

      //Create our JSON root from PARSON
      JSON_Value *quoteRoot;
      //Parse Our String
      quoteRoot = json_parse_string(quoteBuffer->data);

      //Get the value of the return. Should be JSONArray (5)
      int quoteParseResultCode = json_value_get_type(quoteRoot);
      if(quoteParseResultCode == JSONArray)
      {
          //Create our array object.
          JSON_Array *quoteBodyArray = json_value_get_array(quoteRoot);

          //Free up quoteBuffer
          buffer_free(quoteBuffer);

          //Re-init with the signature added.
          quoteBuffer = buffer_new_with_string(quoteBodyArray->items[0]->value.string.chars);
          buffer_append(quoteBuffer, " - Ron Swanson\0");

          //Clean up.
          json_value_free(quoteRoot);
      }
      else {//If the JSON Parse fails.
        printf("failed to parse quote response.\n");
      }
    }
    else {//If not 200 OK
      printf("Error: HTTP GET returned %d\n", res->response_code);
    }

    //Clean Up HTTP Calls
    FREE_HTTP_REQUEST(req);
    FREE_HTTP_RESPONSE(res);

    //Return the buffer.
    return quoteBuffer;
}


// ==== Client Init Functions ====
// As with all C programs start with main:
// Here we can add actions we want when the page loads.
// This will be called on every page load wth bin/app.js included
int main()
{
    //fido call. 
    //Call our quote function.
    buffer_t *quoteBuffer = quote();
    printf("%s\n", quoteBuffer->data);

    //Server Side Rendering
    //LOAD KORE

    //Client Side Rendering

    //==================
    //Fracture Banner
    // Div
    FRACTURE_HTML_ELEMENT* banner = FRACTURE_CREATE_HTML_ELEMENT();//TODO Add f(x) to set Tag Name on Create
    banner = FRACTURE_ADD_NEW_ATTRIBUTE(banner, "tagName", "div");
    banner = FRACTURE_ADD_NEW_ATTRIBUTE(banner, "id", "banner");
    banner = FRACTURE_ADD_NEW_ATTRIBUTE(banner, "className", "flex grid grid-cols-12");

    //BufferCol 
    FRACTURE_HTML_ELEMENT* bufferCol = FRACTURE_CREATE_HTML_ELEMENT();
    bufferCol = FRACTURE_ADD_NEW_ATTRIBUTE(bufferCol, "tagName", "div");
    // bufferCol = FRACTURE_ADD_NEW_ATTRIBUTE(bufferCol, "innerHTML", "div");
    bufferCol = FRACTURE_ADD_NEW_ATTRIBUTE(bufferCol, "className", "col-span-1");
    
    //Title
    FRACTURE_HTML_ELEMENT* title = FRACTURE_CREATE_HTML_ELEMENT();
    title = FRACTURE_ADD_NEW_ATTRIBUTE(title, "tagName", "p");
    title = FRACTURE_ADD_NEW_ATTRIBUTE(title, "id", "bannerTitle");
    title = FRACTURE_ADD_NEW_ATTRIBUTE(title, "className", "col-span-3");
    title = FRACTURE_ADD_NEW_ATTRIBUTE(title, "innerHTML", "FRACTURE UI");

    banner = FRACTURE_ADD_CHILD_ELEMENT(banner, bufferCol);
    banner = FRACTURE_ADD_CHILD_ELEMENT(banner, title);

    char* bannerJSON = FRACTURE_JSON_SERIALIZE_HTML_ELEMENT(banner);
    FRACTURE_APPEND_BODY(bannerJSON);
    free(bannerJSON);

    //==================
    // Quote of the DAY
    //Create Quote DIV
    FRACTURE_HTML_ELEMENT* quoteDiv = FRACTURE_CREATE_HTML_ELEMENT();
    quoteDiv = FRACTURE_ADD_NEW_ATTRIBUTE(quoteDiv, "tagName", "div");
    quoteDiv = FRACTURE_ADD_NEW_ATTRIBUTE(quoteDiv, "id", "quoteDiv");

    //Create our Quote Paragraph
    FRACTURE_HTML_ELEMENT* quoteElement = FRACTURE_CREATE_HTML_ELEMENT();
    quoteElement = FRACTURE_ADD_NEW_ATTRIBUTE(quoteElement, "tagName", "p");
    quoteElement = FRACTURE_ADD_NEW_ATTRIBUTE(quoteElement, "innerHTML", quoteBuffer->data);

    //Add Our Quote Paragraph to our Div
    quoteDiv = FRACTURE_ADD_CHILD_ELEMENT(quoteDiv, quoteElement);

    char* serailizedElement = FRACTURE_JSON_SERIALIZE_HTML_ELEMENT(quoteDiv);
    FRACTURE_APPEND_BODY(serailizedElement);

    free(serailizedElement);
    buffer_free(quoteBuffer);

    return 0;
}
