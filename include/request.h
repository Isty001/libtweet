#ifndef LIBTWEET_PARAM_H
#define LIBTWEET_PARAM_H


#include <stdbool.h>
#include "auth.h"


typedef struct lt_request lt_request;


lt_request *lt_request_create_user(lt_app *app, lt_user *user);

void lt_request_set(lt_request *request, char *key, char *value);

char *lt_request_get(lt_request *request, char *key);

void lt_request_remove(lt_request *request, char *key);

void lt_request_destroy(lt_request *request);


#endif
