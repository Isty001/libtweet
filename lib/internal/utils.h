#ifndef LIBTWEET_INTERNAL_UTILS_H
#define LIBTWEET_INTERNAL_UTILS_H


#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>


#define interface

#ifndef UNIT_TEST
#define internal __attribute__ ((visibility ("internal")))
#else
#define internal
#endif

#define unused(param) param __attribute__((__unused__))


#define die(message) do { perror(message); exit(-1); } while(0)

#define write_callback(callback_name) size_t callback_name(char *response, size_t unused(size), size_t unused(nmemb), void unused(*write_data))


//Todo: log_debug malloc_
#define malloc_(size) ({ \
    void *ptr = malloc(size); \
    if (NULL == ptr) { \
        die("Couldn't allocate memory"); \
    } \
    ptr; \
})

#define alloc_type(data_type) ({ \
    malloc_(sizeof(data_type)); \
})

//Todo: log_debug free
#define free_(ptr) free(ptr)


char *sub_string(char *subject, char *from, char *to);


#endif
