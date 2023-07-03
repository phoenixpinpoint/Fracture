/**
 * @file headers.c
 * @author Adam Guthrie
 * @brief headers.c [tests]
 * 
 *  This file contains the unit tests for the Headers for WebC. 
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
#include "../src/http/utils/headers.h"

/**
 * @brief Create Header and populate with test data.
 * create_header allocates header memory and stores
 * test data for use.
 */
START_TEST (create_header)
{
    printf("Create Header:\n");
    //Create a header pointer. 
    printf("...Test with valid strings\n");
    HEADER *h = CREATE_HEADER("test-key", "test-value");
    ck_assert_int_eq(strncmp("test-key", h->key, strlen("test-key")), 0);
    ck_assert_int_eq(strncmp("test-value", h->value, strlen("test-value")), 0);
    printf("...Test with null strings\n");
    HEADER *n = CREATE_HEADER(NULL, NULL);
    ck_assert_int_eq(n->key, 0);
    ck_assert_int_eq(n->value, 0);
    printf("...Test free with valid strings\n");
    FREE_HEADER(h);
    printf("...Test free with null strings\n");
    FREE_HEADER(n);
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief update header creates and tests each update or state change function.
 */
START_TEST (update_header)
{
    printf("Update Header:\n");
    //Create a header pointer. 
    printf("...Test with valid update key strings\n");
    HEADER *h = CREATE_HEADER("test-key", "test-value");
    SET_KEY(h, "test-key2");
    ck_assert_int_eq(strncmp("test-key2", h->key, strlen("test-key2")), 0);
    printf("...Test with null update key strings\n");
    SET_KEY(h, NULL);
    ck_assert_int_eq(h->key, 0);
    printf("...Test with valid update value strings\n");
    SET_VALUE(h, "test-value2");
    ck_assert_int_eq(strncmp("test-value2", h->value, strlen("test-value2")), 0);
    printf("...Test with null update value strings\n");
    SET_VALUE(h, NULL);
    ck_assert_int_eq(h->value, 0);
    FREE_HEADER(h);
    printf("------------------------------\n");
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
    TCase *tc_headers;

    //Create a suite and tcase
    s = suite_create("HEADER");
    tc_headers = tcase_create("Headers");
    
    //Add our test to the tcase and add the test case to the suite.
    tcase_add_test(tc_headers, create_header);
    tcase_add_test(tc_headers, update_header);
    suite_add_tcase(s, tc_headers);

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