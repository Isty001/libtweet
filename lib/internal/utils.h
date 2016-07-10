#ifndef LIBTWEET_INTERNAL_UTILS_H
#define LIBTWEET_INTERNAL_UTILS_H


#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdarg.h>


#define interface

#define internal __attribute__ ((visibility ("internal")))

#define unused(param) param __attribute__((__unused__))


#define str_starts_with(string, prefix) 0 == strncmp(data, prefix, strlen(prefix))

#define die(message) do { perror(message); exit(-1); } while(0)

#define write_callback(callback_name) size_t callback_name(char *data, size_t unused(size), size_t unused(nmemb), void unused(*write_data))

#define function(return_type, function_body) ({ return_type __fn__ function_body __fn__; })


//Todo: log_debug alloc
#define alloc(size) ({ \
    void *ptr = malloc(size); \
    if (NULL == ptr) { \
        die("Couldn't allocate memory"); \
    } \
    ptr; \
})

#define alloc_type(data_type) ({ \
    alloc(sizeof(data_type)); \
})

//Todo: log_debug free
#define _free(ptr) free(ptr)


#endif
