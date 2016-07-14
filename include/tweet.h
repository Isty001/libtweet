#ifndef LIBTWEET_TWEET_H
#define LIBTWEET_TWEET_H


typedef struct lt_user lt_user;

typedef struct lt_app lt_app;


void lt_init(void);

lt_app *lt_app_create(char *token, char *secret);

void lt_run(void);

void lt_cleanup(void);


#endif
