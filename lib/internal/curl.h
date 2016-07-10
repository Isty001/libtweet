#ifndef LIBTWEET_INTERNAL_CURL_H
#define LIBTWEET_INTERNAL_CURL_H


#include <curl/curl.h>


void curl_init(void);

void curl_cleanup(void);

void curl_request(char *url, curl_write_callback callback);

void curl_request_data(char *url, curl_write_callback callback, void *data);

void curl_request_perform(void);


#endif
