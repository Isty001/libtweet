#ifndef LIBTWEET_AUTH_H
#define LIBTWEET_AUTH_H


#include "tweet.h"


typedef int (*lt_pin_provider)(char *url);

typedef void (*lt_user_auth_callback)(lt_app *app, lt_user *user);


void lt_auth_pin(lt_app *app, lt_pin_provider pin_provider, lt_user_auth_callback user_callback);

void lt_user_destroy(lt_user *user);


#endif
