# Vortex Framework [![Build Status](https://travis-ci.com/ZigaBobnar/vortex.svg?branch=master)](https://travis-ci.com/ZigaBobnar/vortex)
Vortex Framework project. Fast, extensible and easy to use backend framework

Vortex allows you to easily create web application using technology stacks you prefer to use. It uses MVC like pattern using customizable router to parse request url and execute controller to return response as view.


## Features
- **Customizable Router** to make custom url schemes
- **Database** based project/**application structure** - meaning changes can be deployed immediately (caching is work in progress to reduce requests to database engine)
- Page **templating** (components are planned too)
- **Scripting engine** to create custom controllers and make dynamic web applications (currently limited version of **JavaScript** is implemented, planned is full V8-JavaScript support and other languages aswell e.g. Python, Lua, VBScript...)


## Getting started
### Docker container
*Work in progress* - The easiest way to use prebuilt version of this project is to use docker container (yet to be uploaded to Docker Hub when the image is ready to be used)


### Build locally
To build the project yourself you will need:
- **CMake** version 3.10 or higher
- **C++ compiler** (gcc/MSVC)
- **Boost** version 1.72.0 or higher
- **Mongo C driver**
- **Mongo C++ driver**

Firstly you need to initialize CMake by navigating into project build subfolder and run `cmake ..`

Build using `make` or `make -j8` replacing 8 with number of threads you want to use for building.

Run executable `./vortex`
