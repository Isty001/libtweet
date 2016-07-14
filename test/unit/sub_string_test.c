#include <stdarg.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../lib/internal/utils.h"
#include "unit_tests.h"


#define clean_up free(token); free(secret); free(id); free(name)


static void test_sub_string(void **state)
{
    char *url = "oauth_token=MyOauthToken&oauth_token_secret=MyVerySecretOauthToken&user_id=1089910&screen_name=twitterapi";
    char *token, *secret, *name, *id;

    token = sub_string(url, "oauth_token=", "&oauth_token_secret=");
    secret = sub_string(url, "&oauth_token_secret=", "&user_id=");
    id = sub_string(url, "&user_id=", "&screen_name=");
    name = sub_string(url, "&screen_name=", "\0");

    assert_string_equal(token, "MyOauthToken");
    assert_string_equal(secret, "MyVerySecretOauthToken");
    assert_string_equal(id, "1089910");
    assert_string_equal(name, "twitterapi");

    clean_up;
}

void run_sub_string_test(void)
{
    test_case_name("SUB_STRING");

    struct CMUnitTest tests[] = {
            cmocka_unit_test(test_sub_string),
    };
    cmocka_run_group_tests(tests, NULL, NULL);
}

