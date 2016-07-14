#Requests


In order to interact with the APIs on a flexible way, you can build your requests via [lt_get()](../include/request.h) and [lt_post()](../include/request.h).
You need to pass the endpoint you want to send your request to, (for example: statuses/user_timeline) and an instance of lt_request which
holds the required and optional parameters. After a successful [authentication](authentication.md) you can use [lt_request_create_user()](../include/request.h) or [lt_request_create_app()](../include/request.h)
based on the context. 


```C


```
