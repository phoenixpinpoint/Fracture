/**
 * @file check_http.c
 * @author Adam Guthrie
 * @brief check_http.c [tests]
 * 
 *  This file contains the unit tests for the HTTP library. 
 *  
 * @version 0.1
 * @date 2022-11-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/http/http.h"

/**
 * @brief Construct a new start test object
 * test_valid is testing the intial state of the cURL object.
 */
START_TEST (test_valid)
{
    printf("HTTP Client: valid\n");
    //Assert that curl is not null
    bool curlCheck = HTTP_CLIENT_VALID();
    ck_assert_int_eq(curlCheck, 0);
}
END_TEST

/**
 * @brief Construct a new start test object
 * test_init is testing the initialization of the cURL object.
 */
START_TEST (test_init)
{
    printf("HTTP Client: init\n");
    //Init the library
    HTTP_CLIENT_INIT();
    //Assert that curl is not null
    bool curlCheck = HTTP_CLIENT_VALID();
    ck_assert_int_eq(curlCheck, 1);
}
END_TEST

/**
 * @brief Construct a new start test object
 * test_cleanup is testing the cleanup of the cURL object.
 */
START_TEST (test_cleanup)
{
    printf("HTTP Client: cleanup\n");
    //Init the library
    HTTP_CLIENT_CLEANUP();
    //Assert that curl is not null
    bool curlCheck = HTTP_CLIENT_VALID();
    ck_assert_int_eq(curlCheck, 0);
}
END_TEST

/**
 * @brief build a http_suite Suite struct
 * 
 * @return Suite* 
 */
Suite *http_suite(void)
{
    //Declare Suite and TCase pointer
    Suite *s;
    TCase *tc_client;

    //Create a suite and tcase
    s = suite_create("HTTP");
    tc_client = tcase_create("Client");
    
    //Add our test to the tcase and add the test case to the suite.
    tcase_add_test(tc_client, test_valid);
    tcase_add_test(tc_client, test_init);
    tcase_add_test(tc_client, test_cleanup);
    suite_add_tcase(s, tc_client);

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
    s = http_suite();

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