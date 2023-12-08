#include "element.h"

#include <stdio.h>
#include <string.h>

//Create a new HTML Element Structure
FRACTURE_HTML_ELEMENT* FRACTURE_CREATE_HTML_ELEMENT()
{
  //Allocate the element
  FRACTURE_HTML_ELEMENT* element = (FRACTURE_HTML_ELEMENT*)malloc(sizeof(FRACTURE_HTML_ELEMENT));
  element->attributeCount = 0;
  element->childCount = 0;
  return element;//Return our uninitialized element.
}

//Add an attribute key value to an HTML Element
FRACTURE_HTML_ELEMENT* FRACTURE_ADD_ATTRIBUTE(FRACTURE_HTML_ELEMENT* element, char* key, char* value)
{
  //Create a new HTML Attribute
  FRACTURE_HTML_ATTRIBUTE* attribute = FRACTURE_CREATE_ATTRIBUTE(key, value);
  //If this is the first attribute
  if(element->attributeCount == 0)
  {
    element->attributeCount = 1;//Set the attributeCount to 1
    element->attributes = (FRACTURE_HTML_ATTRIBUTE*)malloc(sizeof(FRACTURE_HTML_ATTRIBUTE*));//allocate an new array of attribute pointers
    element->attributes[0] = attribute;//assign attribute to index 0
  }
  //If this is NOT the first attribute
  else {
    int newAttributeIndex= element->attributeCount;//Use the previous attribute count as the new index
    element->attributeCount++;//Increment the attributeCount
    element->attributes = realloc(element->attributes, element->attributeCount*sizeof(FRACTURE_HTML_ATTRIBUTE*));//Re-allocate the attributes array.
    element->attributes[newAttributeIndex] = attribute;//Set the last element in the array equal to the new attribute
  }
  return element;
}

//Create a new attribute struct and return it.
FRACTURE_HTML_ATTRIBUTE* FRACTURE_CREATE_ATTRIBUTE(char* key, char* value)
{
  //Allocate an ATTRIBUTE struct in memory
  FRACTURE_HTML_ATTRIBUTE* attribute = (FRACTURE_HTML_ATTRIBUTE*)malloc(sizeof(FRACTURE_HTML_ATTRIBUTE));

  //Create our key/value buffers
  buffer_t* keyBuffer = buffer_new_with_string(key);
  buffer_t* valueBuffer = buffer_new_with_string(value);

  //Assign our buffers to our attribute
  attribute->key = keyBuffer;
  attribute->value = valueBuffer;

  //Return the attribute
  return attribute;
}

char* FRACTURE_JSON_SERIALIZE_HTML_ELEMENT(FRACTURE_HTML_ELEMENT* element)
{
  JSON_Value *elementValue = json_value_init_object();
  JSON_Object *elementObject = json_value_get_object(elementObject);
  char* serializedObject = NULL;
}
