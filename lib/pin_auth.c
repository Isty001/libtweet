#include <string.h>
#include "internal/auth.h"
#include "internal/curl.h"
#include "internal/user.h"
#include "internal/utils.h"


#define URL_REQUEST_TOKEN "https://api.twitter.com/oauth/request_token?oauth_callback=oob"
#define URL_AUTHORIZE "https://api.twitter.com/oauth/authenticate"
#define URL_ACCESS_TOKEN "https://api.twitter.com/oauth/access_token?oauth_verifier=%d?%s"

#define is_successful_response(response) str_starts_with(response, "oauth_token")


typedef struct
{
    lt_pin_provider pin_provider;
    lt_auth_callback user_callback;
    lt_app *app;
} pin_req_data;


static write_callback(pin_oauth_callback)
{
    pin_req_data *req_dat = (pin_req_data *) write_data;

    if (is_successful_response(data)) {
        req_dat->user_callback(user_create(data));
    } else {
        die(data);
    }

    req_dat->user_callback(user_create(data));
    _free(req_dat);

    return size;
}

static int get_pin_code(pin_req_data *auth, char *data)
{
    char pin_url[300];

    sprintf(pin_url, "%s?%s", URL_AUTHORIZE, data);

    return auth->pin_provider(pin_url);
}

static write_callback(callback)
{
    pin_req_data *req_data = (pin_req_data *) write_data;
    char *signed_url, oauth_url[300];

    if (is_successful_response(data)) {
        sprintf(oauth_url, URL_ACCESS_TOKEN, get_pin_code(req_data, data), data);
        signed_url = auth_sign_url(req_data->app, oauth_url);

        curl_request_data(signed_url, pin_oauth_callback, req_data);
    } else {
        die(data);
    }

    return size;
}

static pin_req_data *create_pin_req_data(lt_app *app, lt_pin_provider provider, lt_auth_callback callback)
{
    pin_req_data *data = alloc_type(pin_req_data);

    data->app = app;
    data->pin_provider = provider;
    data->user_callback = callback;

    return data;
}

interface void lt_auth_pin(lt_app *app, lt_pin_provider pin_provider, lt_auth_callback user_callback)
{
    char *url = auth_sign_url(app, URL_REQUEST_TOKEN);
    pin_req_data *auth_data = create_pin_req_data(app, pin_provider, user_callback);

    curl_request_data(url, callback, auth_data);
}
