# Utils
Utilities is a collection of tools for HTTP uses.

## Request
Request is the HTTP utility for contiainerizing the HTTP Request work for the libcurl interface. As it is right now REQUEST is meerly a struct with a few char* pointers. Ideally there will be additional utility added to this module.

Request is currently the only mechanism approved for submitting a HTTP request in the library.

```
REQUEST req;
req.url = "https://test.com";
req.headers = "";
req.body = "{'test' : 'DATA'}";
```

## Response
Response is the HTTP utitliy for containerizing the HTTP Response work for the libcurl interface. As with Request, Response is the only mechanism.

```
RESPONSE res;
HTTP_GET(req, res); //This function does not exists yet but is meerely a representation.
printf("%d\n", res.status_code);
printf("%s\n", res.body);
printf("%s\n", res.headers);
```