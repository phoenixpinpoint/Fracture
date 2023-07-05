# Client
Client is a lightweight wrapper over cURLs API, providing a more seamless and understandable API.
Currently in scope is GET, POST, PATCH, DELETE.

### API
**HTTP_CLIENT_INIT()** 
HTTP_CLIENT_INIT() must be called in order to initialize cURL for client operations.

**HTTP_CLIENT_CLEANUP()**
HTTP_CLIENT_CLEANUP() must be called in order to cleanup cURL.

**HTTP_CLIENT_VALID()**
HTTP_CLIENT_VALID() checks to see if the curl pointer is valid.

**HTTP_ALLLOW_REDIRECTS(bool)**
HTTP_ALLLOW_REDIRECTS toggles the ability for the client to redirect.

**GET(REQUEST)**
GET is the HTTP get function for the client that handles basic HTTP GET requests. GET takes in a REQUEST which consists of a url, a body an, headers.