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
    printf("...Calling HTTP_CLIENT_VALID\n");
    bool curlCheck = HTTP_CLIENT_VALID();
    printf("...Should Be False\n");
    ck_assert_int_eq(curlCheck, 0);
    printf("------------------------------\n");
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
    printf("...Calling HTTP_CLIENT_INIT\n");
    HTTP_CLIENT_INIT();
    //Assert that curl is not null
    printf("...Calling HTTP_CLIENT_VALID\n");
    bool curl_check = HTTP_CLIENT_VALID();

    ck_assert_int_eq(curl_check, 1);
    printf("------------------------------\n");
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
    printf("...Calling HTTP_CLIENT_CLEANUP\n");
    HTTP_CLIENT_CLEANUP();
    //Assert that curl is not null
    bool curl_check = HTTP_CLIENT_VALID();
    printf("...Checking HTTP_CLIENT_VALID returned false.\n");
    ck_assert_int_eq(curl_check , 0);
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief Construct a new start test object
 * test_create_request test the creation of a reuqest struct
 */
START_TEST (test_create_request)
{
    printf("HTTP Client: REQUEST creation\n");
    //Create a REQUEST
    REQUEST r;
    //Set the url, body, and header
    r.url = "https://test.com";
    r.body = "{'test' : 'hello,world'}";
    r.header = "";
    ck_assert_str_eq(r.url, "https://test.com");
    ck_assert_str_eq(r.body, "{'test' : 'hello,world'}");
    ck_assert_str_eq(r.header, "");
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief Construct a new start test object
 * test_create_response test the creation of a response struct
 */
START_TEST (test_create_response)
{
    printf("HTTP Client: RESPONSE creation\n");
    //Create a RESPONSE
    RESPONSE res; 
    //Test the values
    res.body = "{}";
    res.response_code = 200;
    //res.headersStr = "";
    ck_assert_str_eq(res.body, "{}");
    ck_assert_int_eq(res.response_code, 200);
    //ck_assert_str_eq(res.headersStr, "");
    printf("------------------------------\n");
}
END_TEST

START_TEST(test_headers)
{
    printf("HTTP Client: HEADER and HEADERS\n");
    printf("...Setting up HEADER h1\n");
    HEADER h1;
    h1.key = "location";
    h1.value = "https://www.example.com";
    
    printf("...Setting up Inital Values of HEADERS headers\n");
    HEADERS headers;
    headers.length = 0;
    headers.headers = NULL;
    
    printf("...Calling ADD_HEADER\n");
    headers = ADD_HEADER(headers, h1);
    
    printf("...Checking headers length is 1\n\0");
    ck_assert_int_eq(headers.length, 1);
    
    printf("...Checking headers[0] value and h1 value are equal\n\0");
    ck_assert_str_eq(headers.headers[0]->value, h1.value);
    
    printf("...Checking GET_HEADER_BY_INDEX value and h1 value are equal\n");
    ck_assert_str_eq(GET_HEADER_BY_INDEX(headers, 0)->value, h1.value);
    
    printf("...Setting up HEADER h2\n");
    HEADER h2;
    h2.key = "user";
    h2.value = "TestATest";
    
    printf("...Calling ADD_HEADER\n");
    headers = ADD_HEADER(headers, h2);
    
    printf("...Checking headers length is 2\n\0");
    ck_assert_int_eq(headers.length, 2);
    
    printf("...Checking headers[1] value and h2 value are equal\n\0");
    ck_assert_str_eq(headers.headers[1]->value, h2.value);
    
    printf("...Checking GET_HEADER_BY_INDEX value and h2 value are equal\n");
    ck_assert_str_eq(GET_HEADER_BY_INDEX(headers, 1)->value, h2.value);
    
    printf("...Checking GET_HEADER_BY_KEY value and h1 value equal\n");
    ck_assert_str_eq(GET_HEADER_BY_KEY(headers, "location")->value, h1.value);
    
    printf("...Checking GET_HEADER_BY_KEY value and h2 value equal\n");
    ck_assert_str_eq(GET_HEADER_BY_KEY(headers, "user")->value, h2.value);
    printf("------------------------------\n");
}
END_TEST

START_TEST (test_get_google_wo_redirect)
{
    printf("HTTP Client: GET https://google.com w/o REDIRECT\n");
    printf("...Calling HTTP_CLIENT_INIT\n");
    HTTP_CLIENT_INIT();
    
    printf("...Setting up request to https://google.com\n");
    REQUEST req;
    req.url = "https://google.com";
    
    printf("...Setting up response\n");
    RESPONSE res;
    
    printf("...Calling GET\n");
    res = GET(req);
    
    printf("...Checking Response Code For 301\n");
    ck_assert_int_eq(res.response_code, 301);

    printf("...Calling CLEANUP\n");
    HTTP_CLIENT_CLEANUP();
    printf("------------------------------\n");
}

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
    tcase_add_test(tc_client, test_create_request);
    tcase_add_test(tc_client, test_create_response);
    tcase_add_test(tc_client, test_headers);
    tcase_add_test(tc_client, test_get_google_wo_redirect);
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