/**
 * @file client.c
 * @author Adam Guthrie
 * @brief client.c [tests]
 * 
 *  This file contains the unit tests for the Client library. 
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
#include "../src/http/client/client.h"

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

// /**
//  * @brief Construct a new start test object
//  * test_create_request test the creation of a reuqest struct
//  */
// START_TEST (test_create_request)
// {
//     printf("HTTP Client: REQUEST creation\n");
//     //Create a REQUEST
//     REQUEST r;
//     //Set the url, body, and header
//     r.url = "https://test.com";
//     r.body = "{'test' : 'hello,world'}";
//     //r.header = "";
//     ck_assert_str_eq(r.url, "https://test.com");
//     ck_assert_str_eq(r.body, "{'test' : 'hello,world'}");
//     //ck_assert_str_eq(r.header, "");
//     printf("------------------------------\n");
// }
// END_TEST

// /**
//  * @brief Construct a new start test object
//  * test_create_response test the creation of a response struct
//  */
// START_TEST (test_create_response)
// {
//     printf("HTTP Client: RESPONSE creation\n");
//     //Create a RESPONSE
//     RESPONSE res; 
//     //Test the values
//     res.body = "{}";
//     res.response_code = 200;
//     //res.headersStr = "";
//     ck_assert_str_eq(res.body, "{}");
//     ck_assert_int_eq(res.response_code, 200);
//     //ck_assert_str_eq(res.headersStr, "");
//     printf("------------------------------\n");
// }
// END_TEST

// /**
//  * @brief Construct a new start test object
//  * test_headers creates a HEADER and HEADERS struct to test.
//  */
// START_TEST(test_headers)
// {
//     printf("HTTP Client: HEADER and HEADERS\n");
//     printf("...Setting up HEADER h1\n");
//     HEADER *h1 = CREATE_HEADER("location", "https://example.com");
//     //h1.key = "location";
//     //h1.value = "https://www.example.com";
    
//     printf("...Setting up Inital Values of HEADERS headers\n");
//     HEADERLIST *headers = CREATE_HEADER_LIST();

//     printf("...Calling ADD_HEADER\n");
//     ADD_HEADER(headers, h1);
    
//     printf("...Checking headers length is 1\n\0");
//     ck_assert_int_eq(headers->length, 1);
    
//     printf("...Checking headers[0] value and h1 value are equal\n\0");
//     ck_assert_str_eq(headers->headers[0]->value, h1->value);
    
//     printf("...Checking GET_HEADER_BY_INDEX value and h1 value are equal\n");
//     ck_assert_str_eq(GET_HEADER(headers, 0)->value, h1->value);
    
//     printf("...Setting up HEADER h2\n");
//     HEADER *h2 = CREATE_HEADER("user", "TestATest");
    
//     printf("...Calling ADD_HEADER\n");
//     ADD_HEADER(headers, h2);
    
//     printf("...Checking headers length is 2\n\0");
//     ck_assert_int_eq(headers->length, 2);
    
//     printf("...Checking headers[1] value and h2 value are equal\n\0");
//     ck_assert_str_eq(headers->headers[1]->value, h2->value);
    
//     printf("...Checking GET_HEADER_BY_INDEX value and h2 value are equal\n");
//     ck_assert_str_eq(GET_HEADER(headers, 1)->value, h2->value);
    
//     printf("...Checking GET_HEADER_BY_KEY value and h1 value equal\n");
//     ck_assert_str_eq(GET_HEADER_BY_KEY(headers, "location")->value, h1->value);
    
//     printf("...Checking GET_HEADER_BY_KEY value and h2 value equal\n");
//     ck_assert_str_eq(GET_HEADER_BY_KEY(headers, "user")->value, h2->value);

//     FREE_HEADER(h1);
//     FREE_HEADER(h2);
//     FREE_HEADER_LIST(headers);
//     printf("------------------------------\n");
// }
// END_TEST

/**
 * @brief Construct a new start test object
 * test_get_google_wo_redirect tests going to google.come without redirects enabled.
 */
START_TEST (test_get_google_wo_redirect)
{
    printf("HTTP Client: GET https://google.com w/o REDIRECT\n");
    printf("...Calling HTTP_CLIENT_INIT\n");
    HTTP_CLIENT_INIT();
    
    printf("...Setting up request to https://google.com\n");
    REQUEST *req = CREATE_REQUEST("https://google.com", "", 0);
    printf("...Setting Redirect to false\n");
    HTTP_ALLOW_REDIRECTS(false);
    
    printf("...Calling GET\n");
    RESPONSE *res = GET(req);
    
    printf("...Checking Response Code For 301\n");
    ck_assert_int_eq(res->response_code, 301);

    printf("...Calling CLEANUP\n");
    HTTP_CLIENT_CLEANUP();
    FREE_REQUEST(req);
    for (int header = 0; header < res->headers->length; header++)
    {
        FREE_HEADER(res->headers->headers[header]);
    }
    FREE_RESPONSE(res);
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief Construct a new start test object
 * test_get_google_w_redirect test going to google.com with redirects enabled.
 */
START_TEST (test_get_google_w_redirect)
{
    printf("HTTP Client: GET https://google.com w/ REDIRECT\n");
    printf("...Calling HTTP_CLIENT_INIT\n");
    HTTP_CLIENT_INIT();
    
    printf("...Setting up request to https://google.com\n");
    REQUEST *req = CREATE_REQUEST("https://google.com","",0);

    printf("...Setting Redirect to true\n");
    HTTP_ALLOW_REDIRECTS(true);
    
    printf("...Calling GET\n");
    RESPONSE *res = GET(req);
    
    printf("...Checking Response Code For 200\n");
    ck_assert_int_eq(res->response_code, 200);

    printf("...Calling CLEANUP\n");
    HTTP_CLIENT_CLEANUP();
    FREE_REQUEST(req);
    // for (int header = 0; header < res->headers->length; header++)
    // {
    //     FREE_HEADER(res->headers->headers[header]);
    // }
    // FREE_RESPONSE(res);
    printf("------------------------------\n");
}
END_TEST

// /**
//  * @brief Construct a new start test object
//  * test_multiple_get tests multiple GET calls within the same function.
//  */
// START_TEST (test_multiple_get)
// {
//     printf("HTTP Client: Multiple HTTP GET Requests\n");
//     printf("...Calling HTTP_CLIENT_INIT\n");
//     HTTP_CLIENT_INIT();

//     printf("...Prepare REQUEST 1&2\n");
//     REQUEST *req1 = CREATE_REQUEST("https://purple.com","",0);
//     REQUEST *req2 = CREATE_REQUEST("https://youtube.com","",0);

//     printf("...Prepare RESPONSE\n");
//     RESPONSE res1;
//     RESPONSE res2;

//     printf("...Call GET on REQUEST 1\n");
//     res1 = GET(req1);

//     printf("...Call GET on REQUEST 2\n");
//     res2 = GET(req2);

//     printf("...Check 200 for RESPONSE 1\n");
//     ck_assert_int_eq(res1.response_code, 200);

//     printf("...Check 200 for RESPONSE 2\n");
//     ck_assert_int_eq(res2.response_code, 200);

//     printf("...Calling CLEANUP\n");
//     HTTP_CLIENT_CLEANUP();
//     printf("------------------------------\n");
// }
// END_TEST

// /**
//  * @brief Construct a new start test object
//  * test_get_max_redirect returns the maximum number of redirects.
//  */
// START_TEST (test_get_max_redirect)
// {
//     printf("HTTP Client: Get the max redirect\n");
//     printf("...Calling get max redirect\n");
//     int max = HTTP_GET_MAX_REDIRECTS();
//     ck_assert_int_eq(max, 100);
//     printf("------------------------------\n");
// }
// END_TEST

// /**
//  * @brief Construct a new start test object
//  * test_set_max_redirect tests the setting of the maximum redirects.
//  */
// START_TEST (test_set_max_redirect)
// {
//     printf("HTTP Client: Set the max redirect\n");
//     printf("...Calling set max redirect\n");
//     HTTP_SET_MAX_REDIRECTS(200);

//     printf("...Checking max redirect");
//     int max = HTTP_GET_MAX_REDIRECTS();
//     ck_assert_int_eq(max, 200);

//     printf("...Calling set max redirect to reset.\n");
//     HTTP_SET_MAX_REDIRECTS(100);
//     printf("------------------------------\n");
// }
// END_TEST

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
    //tcase_add_test(tc_client, test_valid);
    //tcase_add_test(tc_client, test_init);
    //tcase_add_test(tc_client, test_cleanup);
    //tcase_add_test(tc_client, test_get_google_wo_redirect);
    tcase_add_test(tc_client, test_get_google_w_redirect);
    // tcase_add_test(tc_client, test_multiple_get);
    // tcase_add_test(tc_client, test_get_max_redirect);
    // tcase_add_test(tc_client, test_set_max_redirect);
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