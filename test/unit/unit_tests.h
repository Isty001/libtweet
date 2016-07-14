#ifndef LIBTWEET_UNITTESTS_H
#define LIBTWEET_UNITTESTS_H


#include <stdio.h>


#define test_case_name(name) printf("\n%s%s:%s\n\n", "\x1B[32m", name, "\x1B[0m");


void run_request_test(void);

void run_sub_string_test(void);


#endif
