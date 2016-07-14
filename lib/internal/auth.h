#ifndef LIBTWEET_INTERNAL_AUTH_H
#define LIBTWEET_INTERNAL_AUTH_H


#include "../../include/auth.h"


char *auth_sign_url_app(char *url, lt_app *app);

char *auth_sign_url_user(char *url, lt_app *app, lt_user *user);

lt_user *user_create(char *oauth_response);


#endif
