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
#include "utils/utils.c"

//Client specific includes
#ifdef CLIENT
    #include "ui/ui.c"
#endif