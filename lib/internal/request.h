#ifndef LIBTWEET_INTERNAL_REQUEST_H
#define LIBTWEET_INTERNAL_REQUEST_H


#include "../../include/request.h"


#define BASE_URL "https://api.twitter.com"


char *parameters_to_query_string(lt_request *request);

char *parameters_to_post_string(lt_request *request);


#endif
