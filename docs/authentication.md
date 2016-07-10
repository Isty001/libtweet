#User authentication

Twitter supports several ways of authentication through oAuth, check the [documentation](https://dev.twitter.com/oauth) for more info.


###PIN based authentication

To complete the PIN based authentication you have to copy the PIN code from the provided URL.
In a terminal application you could do something like this:

```
#include <tweet/auth.h>
#include <tweet/tweet.h>
#include <stdio.h>


int pin_provider(char *url)
{
    int pin;

    printf("Please open the link: %s", url);
    scanf("%d", &pin);

    return pin;
}

void auth_callback(lt_user *user)
{
    //Now you can use the API on the behalf of the authenticated user  
    puts("Authenticated!");
}

int main(void)
{
    lt_init();
    lt_app *app = lt_app_create("YOUR_TOKEN", "YOUR_TOKEN_SECRET");

    lt_auth_pin(app, pin_provider, auth_callback);

    while(some_condition){
        lt_run();
    }

    lt_cleanup();
    
    retun 0;
}

```
