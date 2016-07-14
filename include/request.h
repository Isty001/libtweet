#ifndef LIBTWEET_REQUEST_H
#define LIBTWEET_REQUEST_H


#include "tweet.h"


typedef struct request_params request_params;

typedef struct lt_request lt_request;

typedef void (*lt_callback)(lt_request *request, char *response);

struct lt_request {
    lt_app *app;
    lt_user *user;
    char *endpoint;
    lt_callback callback;
    request_params *params;
};


lt_request *lt_request_create_app(char *endpoint, lt_app *app);

lt_request *lt_request_create_user(char *endpoint, lt_app *app, lt_user *user);

void lt_request_set_param(lt_request *request, char *key, char *value);

char *lt_request_get_param(lt_request *request, char *key);

void lt_request_remove_param(lt_request *request, char *key);

void lt_request_destroy(lt_request *request);

void lt_get(lt_request *request);


#endif
