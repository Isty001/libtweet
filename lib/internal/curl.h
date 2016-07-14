#ifndef LIBTWEET_INTERNAL_CURL_H
#define LIBTWEET_INTERNAL_CURL_H


#include <curl/curl.h>


void curl_init(void);

void curl_cleanup(void);

void curl_request_get(char *url, curl_write_callback callback, void *data);


#endif
