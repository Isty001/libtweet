#include <string.h>
#include <stdio.h>
#include "internal/utils.h"
#include "internal/request.h"
#include "internal/curl.h"
#include "internal/auth.h"


static const char *QUERY_STRING_FORMAT = "%s?%s=%s";
static const char *POST_STRING_FORMAT = "%s%s=%s";
static const char *PARAM_SEPARATOR = "&";


#define return_if_empty(request, _return) if (NULL == request->params->first) return _return;

#define foreach(request)  \
    param *param = request->params->first; \
        while (NULL != param) \

#define set_next(p) param = p

#define next(param) set_next(param->next)

#define key_equals(param, key) 0 == strcmp(param->key, key)


typedef struct param param;


struct param
{
    char *key;
    char *value;
    param *next;
};

struct request_params
{
    param *first;
    param *last;
};

static request_params *create_request_params(void)
{
    request_params *params = alloc_type(request_params);
    params->first = NULL;
    params->last = NULL;

    return params;
}

static lt_request *create_request(char *endpoint, lt_app *app)
{
    lt_request *request = malloc_(sizeof(lt_request) + sizeof(endpoint));
    request->app = app;
    request->endpoint = endpoint;
    request->params = create_request_params();
    request->callback = NULL;

    return request;
}

interface lt_request *lt_request_create_app(char *endpoint, lt_app *app)
{
    return lt_request_create_user(endpoint, app, NULL);
}

interface lt_request *lt_request_create_user(char *endpoint, lt_app *app, lt_user *user)
{
    lt_request *request = create_request(endpoint, app);
    request->user = user;

    return request;
}

interface void lt_request_destroy(lt_request *request)
{
    param *next;

    foreach(request) {
        next = param->next;
        free_(param);
        set_next(next);
    }
    free_(request->params);
    free_(request);
}

static param *create_param(char *key, char *value)
{
    param *new = malloc_(sizeof(param));
    new->key = key;
    new->value = value;
    new->next = NULL;

    return new;
}

interface void lt_request_set_param(lt_request *request, char *key, char *value)
{
    param *param = create_param(key, value);

    if (NULL == request->params->first) {
        request->params->first = param;
    } else {
        request->params->last->next = param;
    }
    request->params->last = param;
}

interface char *lt_request_get_param(lt_request *request, char *key)
{
    return_if_empty(request, NULL);

    foreach(request) {
        if (key_equals(param, key)) {
            return param->value;
        }
        next(param);
    }
    return NULL;
}

static void destroy_parameter(lt_request *request, param *removed, param *prev)
{
    if (removed == request->params->first) {
        request->params->first = removed->next;
    }
    prev->next = removed->next;
    free_(removed);
}

interface void lt_request_remove_param(lt_request *request, char *key)
{
    return_if_empty(request,);

    param *prev = request->params->first;

    foreach(request) {
        if (key_equals(param, key)) {
            destroy_parameter(request, param, prev);

            break;
        }
        prev = param;
        next(param);
    }
}

static char *create_parameter_string(lt_request *request, const char *format)
{
    char *string = "";

    foreach(request) {
        asprintf(&string, format, param->key, param->value);

        if (param != request->params->last) {
            asprintf(&string, "%s%s", string, PARAM_SEPARATOR);
        }
    }
    return string;
}

internal char *parameters_to_query_string(lt_request *request)
{
    return create_parameter_string(request, QUERY_STRING_FORMAT);
}

internal char *parameters_to_post_string(lt_request *request)
{
    return create_parameter_string(request, POST_STRING_FORMAT);
}

static write_callback(lt_get_write_callback)
{
    lt_request *request = write_data;
    request->callback(request, response);

    return size;
}

interface void lt_get(lt_request *request)
{
}
