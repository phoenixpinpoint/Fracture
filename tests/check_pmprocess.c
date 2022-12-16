/**
 * @file check_pmprocess.c
 * @author Adam Guthrie
 * @brief 
 * 
 *  This file contains the unit tests for the PM Process object.
 * 
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../src/processmanager/pmprocess.h"

/**
 * @brief Construct a new start test object
 * create pmprocess
 */
START_TEST (create_pmprocess)
{
	printf("PM Process: create_pmprocess\n");
	//Create a PM Process
	PMProcess testProcess;
	testProcess.pid = 0;
	testProcess.name = (char*)calloc(5, sizeof(char));
	strcpy(testProcess.name, "TEST\0");
	testProcess.status = NEW;
	testProcess.next = NULL;
	//ck_assert_str_eq()
}

Suite *pmprocess_suite(void)
{
	//Setup a Suite and TCase
	Suite *s;
	TCase *tc_client;
	s = suite_create("PMProcess");
	tc_client = tcase_create("process");

	tcase_add_test(tc_client, create_pmprocess);
	suite_add_tcase(s, tc_client);

	return s;
}

int main(void)
{
    int no_failed = 0; // Count of the number of failures
	
	Suite *s;
	SRunner *runner;

	s = pmprocess_suite();

	runner = srunner_create(s);

	srunner_run_all(runner, CK_NORMAL);

	no_failed = srunner_ntests_failed(runner);

	srunner_free(runner);


    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE; 
}
