/**
 * @file fs.c
 * @author Adam Guthrie
 * @brief fs.c [tests]
 * 
 *  This file contains the unit tests for the File System library. 
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
#include "../src/utils/fs.h"

/**
 * @brief Read File uses the read file function.
 */
START_TEST (read_file)
{
    printf("Reading File test.txt\n");
    char* buffer = READ_FILE("../test.txt");
    ck_assert_int_eq(strncmp("Hello, World!", buffer, strlen("Hello, World!")), 0);
    free(buffer);
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief Get Current Working Directory Test
 */
START_TEST (get_cwd)
{
    printf("Getting CWD\n");
    char* buffer = GET_CWD();
    printf("%s\n", buffer);
    ck_assert_int_ne(strncmp("-1", buffer, strlen("-1")), 0);
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief List files LS
 */
START_TEST (list_files)
{
    printf("Listing files\n");
    DIRECTORYLIST *dlist = LIST_FILES("./");
    PRINT_DIRECTORY_LIST(dlist);
    printf("------------------------------\n");
}
END_TEST

/**
 * @brief build a http_suite Suite struct
 * 
 * @return Suite* 
 */
Suite *fs_suite(void)
{
    //Declare Suite and TCase pointer
    Suite *s;
    TCase *tc_fs;

    //Create a suite and tcase
    s = suite_create("FS");
    tc_fs = tcase_create("FS");
    
    //Add our test to the tcase and add the test case to the suite.
    tcase_add_test(tc_fs, read_file);
    tcase_add_test(tc_fs, get_cwd);
    tcase_add_test(tc_fs, list_files);
    suite_add_tcase(s, tc_fs);

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
    s = fs_suite();

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