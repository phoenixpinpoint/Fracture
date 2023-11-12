/*
* appp.c
* This is the start a great thing.
*/

#include "src/fracture.c"

//In this simple function we call the Ron Swanson API
void quote()
{
    //Build our HTTP request with the URL, NULL Headers, NULL Body
    HTTP_REQUEST *req = CREATE_HTTP_REQUEST("https://ron-swanson-quotes.herokuapp.com/v2/quotes",NULL,NULL);
    HTTP_RESPONSE *res = HTTP_GET(req);//Call our HTTP_GET function.

    //Check the response code
    if(res->response_code == 200)
    {
      //Store the quote string
      buffer_t *quoteBuffer = buffer_new_with_string(res->body);

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

          //Print the result to the console.
          printf("%s\n", quoteBuffer->data);

          //Clean up.
          json_value_free(quoteRoot);
          buffer_free(quoteBuffer);
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
}

//As with all C programs start:
int main()
{
    //Call our quote function.
    quote();
    return 0;
}
