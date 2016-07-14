#include <stdio.h>
#include <malloc.h>
#include <oauth.h>
#include <stdlib.h>
#include "internal/auth.h"
#include "internal/utils.h"
#include "internal/request.h"


#define OAUTH_URL_MAX 150
#define SIZE_OF_APP sizeof(lt_app) + sizeof(token) + sizeof(secret)
#define SIZE_OF_USER sizeof(lt_user) + OAUTH_URL_MAX

#define APP_SIGNATURE url, NULL, OA_HMAC, "GET", app->token, app->secret

static const int SIGNED_URL_MAX = 350;


struct lt_user
{
    char *id;
    char *screen_name;
    char *token;
    char *secret;
    char *oauth;
};

struct lt_app
{
    char *token;
    char *secret;
};


interface lt_app *lt_app_create(char *token, char *secret)
{
    lt_app *app = malloc_(SIZE_OF_APP);
    app->token = token;
    app->secret = secret;

    return app;
}

internal lt_user *user_create(char *oauth_response)
{
    lt_user *user = malloc_(SIZE_OF_USER);
    user->token = sub_string(oauth_response, "oauth_token=", "&oauth_token_secret=");
    user->secret = sub_string(oauth_response, "&oauth_token_secret=", "&user_id=");
    user->id = sub_string(oauth_response, "&user_id=", "&screen_name=");
    user->screen_name = sub_string(oauth_response, "&screen_name=", "\0");

    return user;
}

interface void lt_user_destroy(lt_user *user)
{
    free_(user->token);
    free_(user->secret);
    free_(user->id);
    free_(user->screen_name);
    free_(user);
}

internal char *auth_sign_url_app(char *url, lt_app *app)
{
    char signed_[SIGNED_URL_MAX];
    sprintf(signed_, "%s/%s", BASE_URL, url);

    return oauth_sign_url2(APP_SIGNATURE, NULL, NULL);
}

internal char *auth_sign_url_user(char *url, lt_app *app, lt_user *user)
{
}
