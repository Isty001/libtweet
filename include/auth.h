#ifndef LIBTWEET_AUTHENTICATION_H
#define LIBTWEET_AUTHENTICATION_H


#include "user.h"


typedef struct lt_app lt_app;

typedef int (*lt_pin_provider)(char *url);

typedef void (*lt_auth_callback)(lt_user *user);


lt_app *lt_app_create(char *token, char *secret);

void lt_auth_pin(lt_app *app, lt_pin_provider pin_provider, lt_auth_callback user_callback);


#endif
