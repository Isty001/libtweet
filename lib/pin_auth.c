#include <string.h>
#include "internal/auth.h"
#include "internal/curl.h"
#include "internal/utils.h"
#include "internal/request.h"


#define ENDPOINT_REQUEST_TOKEN "oauth/request_token?oauth_callback=oob"
#define ENDPOINT_AUTHORIZE "oauth/authenticate"
#define ENDPOINT_ACCESS_TOKEN "oauth/access_token?oauth_verifier=%d?%s"

#define str_starts_with(string, prefix) 0 == strncmp(string, prefix, strlen(prefix))

#define is_successful_response(response) str_starts_with(response, "oauth_token")


typedef struct
{
    lt_pin_provider pin_provider;
    lt_user_auth_callback callback;
    lt_app *app;
} pin_auth_data;


static write_callback(pin_oauth_callback)
{
    pin_auth_data *auth_dat = write_data;

    if (is_successful_response(response)) {
        auth_dat->callback(auth_dat->app, user_create(response));
    } else {
        die(response);
    }

    free_(auth_dat);

    return size;
}

static int get_pin_code(pin_auth_data *auth, char *data)
{
    char pin_url[300];

    sprintf(pin_url, "%s/%s?%s", BASE_URL, ENDPOINT_AUTHORIZE, data);

    return auth->pin_provider(pin_url);
}

static char *crate_access_token_url(pin_auth_data *req_data, char *response)
{
    char token_url[300];

    sprintf(token_url, ENDPOINT_ACCESS_TOKEN, get_pin_code(req_data, response), response);

    return auth_sign_url_app(token_url, req_data->app);
}

static write_callback(callback)
{
    pin_auth_data *auth_data = write_data;

    if (is_successful_response(response)) {
        char *url = crate_access_token_url(auth_data, response);

        curl_request_get(url, pin_oauth_callback, auth_data);
    } else {
        die(response);
    }

    return size;
}

static pin_auth_data *create_pin_auth_data(lt_app *app, lt_pin_provider provider, lt_user_auth_callback callback)
{
    pin_auth_data *data= malloc_(sizeof(pin_auth_data));
    data->app = app;
    data->pin_provider = provider;
    data->callback = callback;

    return data;
}

interface void lt_auth_pin(lt_app *app, lt_pin_provider pin_provider, lt_user_auth_callback auth_callback)
{
    char *url = auth_sign_url_app(ENDPOINT_REQUEST_TOKEN, app);
    pin_auth_data *auth_data = create_pin_auth_data(app, pin_provider, auth_callback);

    curl_request_get(url, callback, auth_data);
}
