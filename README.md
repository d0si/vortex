# Vortex Framework [![Build Status](https://travis-ci.com/d0si/vortex.svg?branch=master)](https://travis-ci.com/d0si/vortex) ![Build Docker image](https://github.com/d0si/vortex/workflows/Build%20Docker%20image/badge.svg?branch=master)
Vortex Framework project. Fast, extensible and easy to use backend framework

Vortex allows you to easily create web application using technology stacks you prefer to use. It uses MVC like pattern using customizable router to parse request url and execute controller to return response as view.

See the [documentation](https://vortex.d0.si) for more info.

## Features
- **Customizable Router** to make custom url schemes
- **Database** based project/**application structure** - meaning changes can be deployed immediately (caching is work in progress to reduce requests to database engine)
- Page **templating** (components are planned too)
- **Scripting engine** to create custom controllers and make dynamic web applications (currently limited version of **JavaScript** is implemented, planned is full V8-JavaScript support and other languages aswell e.g. Python, Lua, VBScript...)


## Getting started
### Docker container
The simplest way to start the project is using prebuilt docker images. You will need to pull the latest image using `docker pull d0si/vortex:latest` and then run it with `docker run -it d0si/vortex:latest /vortex/build/bin/vortex`. If you replace the last argument with e.g. `/bin/bash` you will have access to the container shell.


### Build locally
To build the project yourself you will need:
- **CMake** version 3.10 or higher
- **C++ compiler** (gcc/MSVC)
- **Boost** version 1.72.0 or higher with development headers
- **OpenSSL** development libraries
- **Mongo C driver** (recommended version 1.16.0)
- **Mongo C++ driver** (recommended version 3.4.0)
- **nlohmann-json** header (recommended version 3.7.3)
- **cpp_redis** with **tacopie**
- **duktape** runtime (recommended version 2.5.0)
- **duktape-cpp**
- **crypto++** (recommended version 8.2.0)
- **libgraphqlparser** (recommended version 0.7.0)

Please take a look at [d0si/cmake-cpp-vortex-builder/blob/master/Dockerfile.alpine](https://github.com/d0si/cmake-cpp-vortex-builder/blob/master/Dockerfile.alpine) to see how the dependencies can be installed and adapt the concept to match your distro.

After cloning the repo you will need to also get submodules. Use `git submodule update --init --recursive` to clone them.

Build steps:
1. Create `build` folder inside project root and cd into it
2. Initialize CMake project using `cmake ..` (Use `-DCMAKE_BUILD_TYPE=Release` argument  to build release binaries)
3. Build using `make` or `make -j8` replacing 8 with number of build jobs (threads) you want to use for building.
4. Run executable with sample project `./bin/vortex --config=../samples/server_config.json`
