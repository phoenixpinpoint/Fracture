/**
 * @file webc.c
 * @author Adam Guthrie
 * @brief webc.c
 * 
 *  Source file to include the entirety WebC.
 * 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

//Standard includes
#include "http/http.c"
#include "../deps/buffer/buffer.c"
#include "../deps/butterknife/butterknife.c"
#include "../deps/cwalk/cwalk.c"
#include "../deps/fs/fs.c"
#include "../deps/tiny-regex-c/re.c"
#include "../deps/vec/vec.c"

//Client specific includes
#ifdef CLIENT
    #include "ui/ui.c"
#endif