#include <stdarg.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/request.h"
#include "unit_tests.h"


#define get_request lt_request *request = *state


lt_app *app;


static int setup(void **state)
{
    *state = (void *) lt_request_create_app("statuses/timeline", app);

    return 0;
}

static void test_set(void **state)
{
    get_request;

    lt_request_set_param(request, "key", "value");
    lt_request_set_param(request, "key2", "val2");


    assert_string_equal("value", lt_request_get_param(request, "key"));
    assert_string_equal("val2", lt_request_get_param(request, "key2"));

    assert_null(lt_request_get_param(request, "nothing"));
}

static void test_remove(void **state)
{
    get_request;

    lt_request_remove_param(request, "key");

    assert_null(lt_request_get_param(request, "key"));
}

static int teardown(void **state)
{
    lt_request_destroy(*state);

    return 0;
}

void run_request_test(void)
{
    test_case_name("REQUEST");

    struct CMUnitTest tests[] = {
            cmocka_unit_test(test_set),
            cmocka_unit_test(test_remove)
    };
    cmocka_run_group_tests(tests, setup, teardown);
}

