#include <string.h>
#include <stdio.h>
#include "internal/utils.h"
#include "../include/request.h"


#define SIZE_OF_PARAM sizeof(param) + sizeof(key) + sizeof(value) + sizeof(param *)

#define QUERY_STRING_FORMAT "%s?%s=%s"

#define POST_STRING_FORMAT "%s%s=%s"

#define return_if_empty(request, _return) if (NULL == request->first_param) return _return;

#define foreach(request)  \
    param *param = request->first_param; \
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

struct lt_request
{
    lt_app *app;
    lt_user *user;
    param *first_param;
    param *last_param;
};

interface lt_request *lt_request_create_app(lt_app *app)
{
    lt_request *request = alloc_type(lt_request);
    request->first_param = NULL;
    request->app = app;

    return request;
}

interface lt_request *lt_request_create_user(lt_app *app, lt_user *user)
{
    lt_request *request = lt_request_create_app(app);
    request->user = user;

    return request;
}

interface void lt_request_destroy(lt_request *request)
{
    param *next;

    foreach(request) {
        next = param->next;
        _free(param);
        set_next(next);
    }
    _free(request);
}

static param *create_param(char *key, char *value)
{
    param *new = alloc(SIZE_OF_PARAM);
    new->key = key;
    new->value = value;
    new->next = NULL;

    return new;
}

interface void lt_request_set(lt_request *request, char *key, char *value)
{
    param *param = create_param(key, value);

    if (NULL == request->first_param) {
        request->first_param = param;
    } else {
        request->last_param->next = param;
    }
    request->last_param = param;
}

interface char *lt_request_get(lt_request *request, char *key)
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

static void remove_param(lt_request *request, param *removed, param *prev)
{
    if (removed == request->first_param) {
        request->first_param = removed->next;
    }
    prev->next = removed->next;
    _free(removed);
}

interface void lt_request_remove(lt_request *request, char *key)
{
    return_if_empty(request,);

    param *prev = request->first_param;

    foreach(request) {
        if (key_equals(param, key)) {
            remove_param(request, param, prev);

            break;
        }
        prev = param;
        next(param);
    }
}

static char *create_request_string(lt_request *context, char *format)
{
}

internal char *to_query_string(lt_request *request)
{
    return create_request_string(request, QUERY_STRING_FORMAT);
}

internal char *to_post_string(lt_request *request)
{
    return create_request_string(request, POST_STRING_FORMAT);
}
