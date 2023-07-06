/**
 * @file webc.h
 * @author Adam Guthrie
 * @brief webc.h
 * 
 *  Header file to include the entirety WebC.
 * 
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */


//Ensure -D SERVER or -D CLIENT is in compiler args
#if !defined(SERVER) && !defined(CLIENT)
#error either SERVER or CLIENT must be defined.
#endif

//Ensure -D SERVER and -D CLIENT are not compiler args together
#if defined(SERVER) && defined(CLIENT)
#error only SERVER or CLIENT can be defined not both.
#endif

//Standard includes
#include "http/http.h"
#include "utils/utils.h"

//Client specific includes
#ifdef CLIENT
  #include "ui/ui.h"
#endif