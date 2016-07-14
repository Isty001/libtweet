#include <stdbool.h>
#include "internal/utils.h"
#include "internal/curl.h"


CURLM *curl_multi;
int req_num;


internal void curl_init(void)
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl_multi = curl_multi_init();
}

internal void curl_cleanup(void)
{
    curl_global_cleanup();
    curl_multi_cleanup(curl_multi);
}

static CURL *create_curl_handle(char *url, curl_write_callback callback)
{
    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);

    return curl;
}

internal void curl_request_get(char *url, curl_write_callback callback, void *data)
{
    CURL *handle = create_curl_handle(url, callback);

    curl_easy_setopt(handle, CURLOPT_WRITEDATA, data);
    curl_multi_add_handle(curl_multi, handle);
}

//Todo: Check status/error
interface void lt_run(void)
{
    curl_multi_perform(curl_multi, &req_num);
}
