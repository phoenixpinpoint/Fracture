/**
 * @file renderer.h
 * @author Adam C. Guthrie
 * @brief renderer.h
 *
 *  Renderer loads assets in the system and renders based on the DOM
 *
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023
 */
#ifndef RENDERER_H
#define RENDERER_H

#include "element.h"

#include <emscripten.h>
#include <butterknife/butterknife.h>

void FRACTURE_WRITE_DOCUMENT(char* page);

void FRACTURE_CREATE_ELEMENT(char* tag, char* id);

void FRACTURE_APPEND_CHILD(char* id, char* elementId);

void FRACTURE_UPDATE_ELEMENT(char* parentId, char* element);

void FRACTURE_APPEND_BODY(char* element);

//
// void ADD_SCRIPT_TO_HEAD(char* script);
//
//
// void wc_write_document(char* page);
//
// void wc_render_page(char* page);
//
// void ADD_SCRIPTS();

#endif
