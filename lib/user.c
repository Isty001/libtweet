#include <malloc.h>
#include "internal/user.h"
#include "internal/utils.h"

#define OAUTH_URL_MAX 150


struct lt_user
{
    char *oauth_url;
};


interface void lt_user_destroy(lt_user *user)
{
    free(user->oauth_url);
    free(user);
}

internal lt_user *user_create(char *oauth_url)
{
    lt_user *user = alloc_type(lt_user);

    user->oauth_url = alloc(OAUTH_URL_MAX);
    user->oauth_url = oauth_url;

    return user;
}
