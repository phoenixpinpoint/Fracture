/**
 * @file regex.c
 * @author Adam Guthrie
 * @brief regex.c [tests]
 * 
 *  This file contains the unit tests for the REGEX library. 
 *  
 * @version 0.1
 * @date 2023-07-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/utils/regex.h"

/**
 * @brief REGEX
 */
START_TEST (regextest)
{
    printf("REGEX Test");
    char* value = "Hello World\0";
    
    REGEX_INIT();

    REGEX_PATTERN("Hello");

    REGEX_PARSE(value);

    REGEX_MATCHES matches;
    matches = INITIALIZE_MATCHES(matches);
    matches = GET_MATCHES(matches);

    printf("Match Count: %d\n", matches.count);

    for(int i = 0; i < matches.count; i++)
    {
        printf("Match %d: %s\n", i, matches.strings[i]);
    }

    REGEX_FREE();
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief build a http_suite Suite struct
 * 
 * @return Suite* 
 */
Suite *regex_suite(void)
{
    //Declare Suite and TCase pointer
    Suite *s;
    TCase *tc_regex;

    //Create a suite and tcase
    s = suite_create("REGEX");
    tc_regex = tcase_create("REGEX");
    
    //Add our test to the tcase and add the test case to the suite.
    tcase_add_test(tc_regex, regextest);
    suite_add_tcase(s, tc_regex);

    return s;
}

/**
 * @brief main actually runs the cases and handles coutns.
 * 
 * @return int 
 */
int main(void){
    int no_failed = 0; //Failure Flag

    //Declare structs
    Suite *s;
    SRunner *runner;

    //Set s to http_suite
    s = regex_suite();

    //Build our runner from s
    runner = srunner_create(s);

    //Run all the tests
    srunner_run_all(runner, CK_NORMAL);

    //Save the number of failures
    no_failed = srunner_ntests_failed(runner);

    //Clean up srunner
    srunner_free(runner);

    //Depending on if no_failed is 0 or greater exit.
    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE; 
}