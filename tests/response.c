/**
 * @file response.c
 * @author Adam Guthrie
 * @brief response.c [tests]
 * 
 *  This file contains the unit tests for Response for WebC. 
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
#include "../src/http/headers.h"
#include "../src/http/response.h"

/**
 * @brief Create a Response object.
 */
START_TEST (create_response)
{
	printf("Create Response:\n");
    RESPONSE *res = CREATE_RESPONSE(200, "", 0);
	ck_assert_int_eq(strcmp(res->body, ""), 0 );

	FREE_RESPONSE(res);	
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief Update a Request object.
 */
START_TEST (update_response)
{
	printf("Update Response:\n");
    RESPONSE *res = CREATE_RESPONSE(200, "", 0);
    ck_assert_int_eq(strcmp(res->body, ""), 0 );

    SET_RESPONSE_BODY(res, "TEST");
    ck_assert_int_eq(strcmp(res->body, "TEST"), 0 );
	
    FREE_RESPONSE(res);
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief build a http_suite Suite struct
 * 
 * @return Suite* 
 */
Suite *response_suite(void)
{
    //Declare Suite and TCase pointer
    Suite *s;
    TCase *tc_response;

    //Create a suite and tcase
    s = suite_create("RESPONSE");
    tc_response = tcase_create("Responses");
    
    //Add our test to the tcase and add the test case to the suite.
    tcase_add_test(tc_response, create_response);
    tcase_add_test(tc_response, update_response);
    suite_add_tcase(s, tc_response);

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
    s = response_suite();

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
