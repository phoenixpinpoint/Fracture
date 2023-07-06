# WebC
## General Overview

WebC is a lightweight modernization framework for C targetted at web development. WebC enables developers to build modernized C applications geared toward web systems. The framework is being designed to be compatible with WebAssembly or native applications on servers.

In this effort there are two main build targets *server* and *client*. 

### Server
Server builds to the local target. This relies on Linux libraries and is currently not supported for windows(that is coming....I promise).

### Client
Client builds to WASM and and JS. 

## Server Environment
WebC is currently only ported for Linux. Any ports to other environments are welcome.

WebC requires the following packages:
libcurl (Tested with OpenSSL version)
libcheck (Unit Testing)

## Building

## Development
### Required Packages For Server
- libcheck
- libcurl

### Required Packages For Client
- emscripten

### Build Webc Server
From the root directory 
```
make server
```

To clean up
```
make clean
```

### Build Webc client
From the root directory 
```
make client
```

To clean up
```
make clean
```

### Tests(Server Only)
From the root directory 
```
make testserver
```

To clean up
```
make clean
```

## Contributing
To contribute please fork a copy of the repo make changes and open a Pull Request. Any and all Pull Request will be reviewed and either added or discussed.