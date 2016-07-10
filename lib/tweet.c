#include "internal/curl.h"
#include "internal/utils.h"


interface void lt_init(void)
{
    curl_init();
}

interface void lt_cleanup(void)
{
    curl_cleanup();
}

interface void lt_run(void)
{
    curl_request_perform();
}
