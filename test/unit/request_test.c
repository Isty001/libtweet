#include <stdarg.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/request.h"


lt_user *user;
lt_app *app;


#define get_request lt_request *request = *state


static int setup(void **state)
{
    *state = (void *) lt_request_create_user(app, user);

    return 0;
}

static void test_set(void **state)
{
    get_request;

    lt_request_set(request, "key", "value");
    lt_request_set(request, "key2", "val2");

    assert_string_equal("value", lt_request_get(request, "key"));
    assert_string_equal("val2", lt_request_get(request, "key2"));

    assert_null(lt_request_get(request, "nothing"));
}

static void test_remove(void **state)
{
    get_request;

    lt_request_remove(request, "key");

    assert_null(lt_request_get(request, "key"));
}

static int teardown(void **state)
{
    lt_request_destroy(*state);

    return 0;
}

void run_request_test(void)
{
    struct CMUnitTest tests[] = {
            cmocka_unit_test(test_set),
            cmocka_unit_test(test_remove)
    };
    cmocka_run_group_tests(tests, setup, teardown);
}

