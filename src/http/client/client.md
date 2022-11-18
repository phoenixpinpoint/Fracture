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