/*
* app.c
* This is the start a great thing.
*/

#include <fracture.c>

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
    //Call our quote function.
    buffer_t *quoteBuffer = quote();
    printf("%s\n", quoteBuffer->data);
    buffer_free(quoteBuffer);

    FRACTURE_HTML_ELEMENT* myDiv = FRACTURE_CREATE_HTML_ELEMENT();
    myDiv = FRACTURE_ADD_ATTRIBUTE(myDiv, "tagName", "div");
    myDiv = FRACTURE_ADD_ATTRIBUTE(myDiv, "id", "myDiv");

    printf("myDiv AttribCount = %d\n", myDiv->attributeCount);

    for (int attribute = 0; attribute < myDiv->attributeCount; attribute++)
    {
      printf("ATTR KEY:VALUE %s:%s\n", myDiv->attributes[attribute]->key->data ,myDiv->attributes[attribute]->value->data);
    }

    JSON_Value *element_value = json_value_init_object();
    JSON_Object *element_object = json_value_get_object(element_value);
    char* serializedObject = NULL;

    // json_object_set_string(element_object, "tagName", "div");
    // json_object_set_string(element_object, "id", "someNewId");
    //
    // serializedObject = json_serialize_to_string(element_value);
    //
    // FRACTURE_APPEND_BODY(serializedObject);
    //
    // json_free_serialized_string(serializedObject);
    // json_value_free(element_value);

    return 0;
}
