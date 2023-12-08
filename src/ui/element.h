/**
 * @file element.h
 * @author Adam C. Guthrie
 * @brief element.h
 *
 *  Element represents an HTML element
 *
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023
 */

#ifndef ELEMENT_H
#define ELEMENT_H

typedef struct FRACTURE_HTML_ATTRIBUTE {
  buffer_t* key;
  buffer_t* value;
} FRACTURE_HTML_ATTRIBUTE;

typedef struct FRACTURE_HTML_ELEMENT {
  void* parent;
  int attributeCount;
  FRACTURE_HTML_ATTRIBUTE** attributes;
  int childCount;
  void** children;

} FRACTURE_HTML_ELEMENT;

FRACTURE_HTML_ELEMENT* FRACTURE_CREATE_HTML_ELEMENT();

FRACTURE_HTML_ELEMENT* FRACTURE_ADD_ATTRIBUTE(FRACTURE_HTML_ELEMENT* element, char* key, char* value);

FRACTURE_HTML_ATTRIBUTE* FRACTURE_CREATE_ATTRIBUTE(char* key, char* value);

char* FRACTURE_JSON_SERIALIZE_HTML_ELEMENT(FRACTURE_HTML_ELEMENT* element);

#endif
