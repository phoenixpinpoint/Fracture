# Fracture
## General Overview

Fracture is a lightweight modernization framework for C targeted at web development. Fracture enables developers to build modernized C applications geared toward web systems. The framework is designed to be compatible with WebAssembly or Javascript applications.

Fracture can be used in conjuction with Kore (https://kore.io/) to build robust C frontend and backend applications.

WASI (https://github.com/WebAssembly/WASI) server side bindings are planned and we would love to have contributions for a WASI server.

## Setup & Building
### Dependencies
- emscripten (https://emscripten.org/) - Used to compile to WASM/JS
- clib (https://github.com/clibs/clib) - Used to install the clibs.json dependencies
- NPM/Node.js (https://www.npmjs.com/ & https://nodejs.org/en)
- Tailwind CSS (https://tailwindcss.com/docs/installation)

### Installation Steps
Follow each dependencies directions:
1) Install Emscripten
2) Install Clibs
3) Install Node.js
4) Install NPM
5) Install Taildwind CSS


### Build Webc client
From the root directory
```
make all
```

To clean up
```
make clean
```
## Contributing
To contribute please fork a copy of the repo make changes and open a Pull Request. Any and all Pull Request will be reviewed and either added or discussed.
