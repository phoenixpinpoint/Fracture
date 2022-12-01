# WebC
## General Overview

WebC is a lightweight modernization framework for C targetted at web development. WebC enables developers to build modernized C applications geared toward web systems. The framework is being designed to be very compatible with WebAssembly or Server Side Applications.

## Environment
WebC is currently only ported for Linux. Any ports to other environments are welcome.

WebC requires the following packages:
libcurl (Tested with OpenSSL version)
libcheck (Unit Testing)

## Building

## Development
### Required Packages
- libcheck
- libcurl

### Client Tests
From the root directory 
```
make TEST
```

To clean up
```
make CLEAN_TEST
```

## Contributing
To contribute please fork a copy of the repo make changes and open a Pull Request. Any and all Pull Request will be reviewed and either added or discussed.