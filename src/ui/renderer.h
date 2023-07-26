/**
 * @file renderer.h
 * @author Adam C. Guthrie
 * @brief renderer.h
 * 
 *  Renderer loads assets in the system and renders based on the DOMS
 * 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 */
#ifndef RENDERER_H
#define RENDERER_H

#include <emscripten.h>
#include "../../deps/butterknife/butterknife.h"

void SET_BODY_INNER_HTML(char* body);

void SET_HEAD_INNER_HTML(char* body);

void ADD_SCRIPT_TO_HEAD(char* script);

void SET_INNER_HTML_BY_ID(char* id, char* body);

void wc_write_document(char* page);

void wc_render_page(char* page);

void ADD_SCRIPTS();

#endif