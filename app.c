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
    // Load the homepage.
    buffer_t* bodyHTML = bk_generate_webpage("../assets/pages/home.bk.html");
    FRACTURE_HTML_ELEMENT* rawBody = FRACTURE_CREATE_HTML_ELEMENT();
    rawBody = FRACTURE_ADD_NEW_ATTRIBUTE(rawBody, "tagName", "div");
    rawBody = FRACTURE_ADD_NEW_ATTRIBUTE(rawBody, "className", "flex flex-col");
    rawBody = FRACTURE_ADD_NEW_ATTRIBUTE(rawBody, "innerHTML", bodyHTML->data);

    char* rawBodyJSON = FRACTURE_JSON_SERIALIZE_HTML_ELEMENT(rawBody);

    FRACTURE_APPEND_BODY(rawBodyJSON);

    free(rawBodyJSON);
    buffer_free(bodyHTML);

    //==================
    // Quote of the DAY
    // Create our element that is to be updated
    FRACTURE_HTML_ELEMENT* quoteElement = FRACTURE_CREATE_HTML_ELEMENT();
    quoteElement = FRACTURE_ADD_NEW_ATTRIBUTE(quoteElement, "innerHTML", quoteBuffer->data);
    char* serailizedElement = FRACTURE_JSON_SERIALIZE_HTML_ELEMENT(quoteElement);
    FRACTURE_UPDATE_ELEMENT("quote", serailizedElement);

    free(serailizedElement);
    buffer_free(quoteBuffer);

    return 0;
}
