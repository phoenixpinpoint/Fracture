/**
 * @file request.c
 * @author Adam Guthrie
 * @brief request.c [tests]
 * 
 *  This file contains the unit tests for Requests for WebC. 
 *  
 * @version 0.1
 * @date 2023-07-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/http/utils/request.h"

/**
 * @brief Create a Request object.
 */
START_TEST (create_request)
{
	printf("Create Request:\n");
    	REQUEST *req = CREATE_REQUEST("https://google.com", "", 0);
	printf("REQUEST_URL: *%s*\n", req->url);
	ck_assert_int_eq(strcmp(req->url, "https://google.com"), 0 );
	FREE_REQUEST(req);	
    	printf("------------------------------\n");
}
END_TEST

/**
 * @brief build a http_suite Suite struct
 * 
 * @return Suite* 
 */
Suite *request_suite(void)
{
    //Declare Suite and TCase pointer
    Suite *s;
    TCase *tc_request;

    //Create a suite and tcase
    s = suite_create("REQUEST");
    tc_request = tcase_create("Requests");
    
    //Add our test to the tcase and add the test case to the suite.
    tcase_add_test(tc_request, create_request);
    suite_add_tcase(s, tc_request);

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
    s = request_suite();

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
