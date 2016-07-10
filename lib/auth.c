#include <stdio.h>
#include <malloc.h>
#include <oauth.h>
#include <stdlib.h>
#include "internal/auth.h"
#include "internal/utils.h"


struct lt_app
{
    char *token;
    char *secret;
};


interface lt_app *lt_app_create(char *token, char *secret)
{
    lt_app *app = alloc_type(lt_app);
    app->token = token;
    app->secret = secret;

    return app;
}

internal char *auth_sign_url(lt_app *app, char *url)
{
    char *signed_url = oauth_sign_url2(url, NULL, OA_HMAC, "GET", app->token, app->secret, NULL, NULL);

    return  signed_url;
}

