#include <string.h>
#include "internal/utils.h"


internal char *sub_string(char *subject, char *from, char *to)
{
    char *first = strstr(subject, from) + strlen(from);
    char *second = strstr(first, to);
    size_t len;

    if (0 != strcmp(first, second)) {
        len = second - first;
    } else {
        len = strlen(first);
    }

    char *res = malloc(sizeof(char) * (len + 1));

    strncpy(res, first, len);
    res[len] = '\0';

    return res;
}
