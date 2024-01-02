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

//Add an attribute to an HTML Element
FRACTURE_HTML_ELEMENT* FRACTURE_ADD_ATTRIBUTE(FRACTURE_HTML_ELEMENT* element, FRACTURE_HTML_ATTRIBUTE* attribute)
{
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

//Add an attribute key value to an HTML Element
FRACTURE_HTML_ELEMENT* FRACTURE_ADD_NEW_ATTRIBUTE(FRACTURE_HTML_ELEMENT* element, char* key, char* value)
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

FRACTURE_HTML_ELEMENT* FRACTURE_ADD_CHILD_ELEMENT(FRACTURE_HTML_ELEMENT* element, FRACTURE_HTML_ELEMENT* child)
{
  //If this is the first 
  if(element->childCount == 0)
  {
    element->childCount = 1;//Set the childCount to 1
    element->children = (void*)malloc(sizeof(FRACTURE_HTML_ELEMENT*));//allocate an new array of child element pointers
    element->children[0] = (void*)child;//assign child to index 0
  }
  //If this is NOT the first child
  else {
    int newChildIndex= element->childCount;//Use the previous child count as the new index
    element->childCount++;//Increment the achildCount
    element->children = realloc(element->children, element->childCount*sizeof(FRACTURE_HTML_ELEMENT*));//Re-allocate the children array.
    element->children[newChildIndex] = (void*)child;//Set the last element in the array equal to the new chid
  }
  return element;
}

//TODO add JSON_Status checks to our fx calls
char* FRACTURE_JSON_SERIALIZE_HTML_ELEMENT(FRACTURE_HTML_ELEMENT* element)
{
  char* serializedObject = NULL;

  JSON_Value *elementValue = FRACTURE_HTML_ELEMENT_TO_JSON(element);

  serializedObject = json_serialize_to_string(elementValue);

  //json_free_serialized_string(serializedObject);
  json_value_free(elementValue);

  return serializedObject;
}

JSON_Value* FRACTURE_HTML_ELEMENT_TO_JSON(FRACTURE_HTML_ELEMENT* element)
{
  JSON_Value *elementValue = json_value_init_object();
  JSON_Object *elementObject = json_value_get_object(elementValue);

  //Serialize the Attributes
  for (int attribute = 0; attribute < element->attributeCount; attribute++)
  {
    json_object_set_string(elementObject, element->attributes[attribute]->key->data, element->attributes[attribute]->value->data);
  }

  JSON_Value* childrenArrayValue = json_value_init_array();
  JSON_Array *children = json_value_get_array(childrenArrayValue);

  if(json_type(childrenArrayValue) != 5)
  {
    printf("ARRAY CREATION FAILURE.\n");
    return elementValue;
  }

  //Serialize the Children
  for (int child = 0; child < element->childCount; child++)
  {
    JSON_Value *childValue;
    FRACTURE_HTML_ELEMENT* childAsElement = (FRACTURE_HTML_ELEMENT*)element->children[child]; 
    // printf("CHILD %d TAG %s\n", child, childAsElement->attributes[0]->value->data);
    childValue = FRACTURE_HTML_ELEMENT_TO_JSON(childAsElement);
    JSON_Status arrayStat = json_array_append_value(children, childValue);
    if (arrayStat == -1)
    {
      printf("Array Status Is JSONError.\n");
      return elementValue;
    }
  }

  JSON_Status objectStat = json_object_set_value(elementObject, "children", childrenArrayValue);
  if (objectStat == -1)
  {
    printf("Object Status Is JSONError.\n");
  }

  return elementValue;
}
