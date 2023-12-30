/**
 * @file renderer.c
 * @author Adam C. Guthrie
 * @brief renderer.c
 *
 *  Renderer loads assets in the system and renders based on the DOM
 *
 * @version 0.1
 * @date 2023-07-05
 *
 * @copyright Copyright (c) 2023
 */
#include "renderer.h"

EM_JS(void, FRACTURE_WRITE_DOCUMENT, (char* page), {
    document.write(UTF8ToString(page));
    return;
});

EM_JS(void, FRACTURE_APPEND_CHILD, (char* parentId, char* childJSON), {
    // let parent = document.getElementById(UTF8ToString(parentId));
    
    // let parsedElement;
    // try {
    //     parsedElement = await JSON.parse(UTF8ToString(childJSON));
    // } catch {
    //   console.log("Element failed to parse.");
    // }

    // console.log(parsedElement);

    // if(!parsedElement.tagName)
    // {
    //   console.log("Tag Specification Missing.");
    // }

    // let element = document.createElement(parsedElement.tagName);

    // if(parsedElement.id)
    // {
    //   element.id = parsedElement.id;
    // }

    // if(parsedElement.childCount > 0)
    // {
    //   // for(int child = 0; child < parsedElement.childCount; child++)
    //   // {
    //   //   try
    //   // }
    // }

    // document.body.appendChild(element);

    // if(child && parent)
    // {
    //   parent.appendChild(child);
    // }
    // else {
    //   console.log("FRACTURE_APPEND_CHILD FAILED.");
    // }
    // return;
});

//Takes an Element JSON object, creates an HTML Element, appends it to the body Element.
EM_ASYNC_JS(void, FRACTURE_APPEND_BODY, (char *elementJson), {
    let parsedElement;
    try {
        parsedElement = await JSON.parse(UTF8ToString(elementJson));
    } catch {
      console.log("Element failed to parse.");
    }

    function generateElement(inputElement)
    {
      let atributeList;
      try {
        attributeList = Object.keys(inputElement);
      } catch {
        console.log("Element failed to parse correctly.");
      }

      let element = document.createElement(inputElement.tagName);
      for (let attribute = 0; attribute < attributeList.length; attribute++)
      {
        if (attributeList[attribute] != "tagName")
        {
          element[attributeList[attribute]] = inputElement[attributeList[attribute]];
        }
      }

      for (let child = 0 ; child < inputElement.children.length; child++)
      {
        if(!inputElement.children[child].tagName)
        {
          console.log("Children Tag Specification Missing.");
        }

        //console.log("Appending child");
        element.appendChild(generateElement(inputElement.children[child]));        
      }
      //console.log("ELEMENT:", element);
      return element;
    }

    //console.log(parsedElement);

    if(!parsedElement.tagName)
    {
      console.log("Tag Specification Missing.");
    }

    let renderedElement = generateElement(parsedElement);

    document.body.appendChild(renderedElement);

    return;
});

// EM_JS(void, SET_INNER_HTML_BY_ID, (char* id, char* body), {
//     document.getElementById(UTF8ToString(id)).innerHTML = UTF8ToString(body);
//     return;
// });
//
// EM_JS(void, SET_BODY_INNER_HTML, (char* body), {
//     document.body.innerHTML = UTF8ToString(body);
//     return;
// });
//
// EM_JS(void, SET_HEAD_INNER_HTML, (char* body), {
//     document.head.innerHTML = UTF8ToString(body);
//     return;
// });
//

//
// void wc_render_page(char* pagePath)
// {
//     buffer_t* renderedPage = bk_generate_webpage(pagePath);
//     wc_write_document(renderedPage->data);
// }
//
// EM_JS(void, ADD_SCRIPT_TO_HEAD, (char* script), {
//     var newScript = document.createElement("script");
//     newScript.type
//             = 'text/javascript';
//     var inlineScript = document.createTextNode(UTF8ToString(script));
//     newScript.appendChild(inlineScript);
//     document.head.appendChild(newScript);
//     return;
// });
//
// void ADD_SCRIPTS()
// {
//     // //Get all scripts in assets/scripts
//     // DIRECTORYLIST *scripts = LIST_FILES("assets/scripts");
//
//     // //For each script file.
//     // for (int iteration = 0; iteration < scripts->length; iteration++)
//     // {
//     //     //Store the file name and allocate a string for the path
//     //     char* scriptFileName = scripts->directories[iteration]->d_name;
//     //     char* scriptPath = calloc(strlen("assets/scripts/")+strlen(scriptFileName), sizeof(char));
//
//     //     //append "assets/scripts" and the directory name
//     //     strncat(scriptPath, "assets/scripts/", strlen("assets/scripts/"));
//     //     strncat(scriptPath, scriptFileName, strlen("assets/scripts/") + strlen(scriptFileName));
//
//     //     //Load the file into a buffer and add the script to the document head.
//     //     char* scriptInstance = READ_FILE(scriptPath);
//     //     ADD_SCRIPT_TO_HEAD(scriptInstance);
//
//     //     //Clean up the buffers
//     //     free(scriptInstance);
//     //     free(scriptPath);
//     // }
// }
