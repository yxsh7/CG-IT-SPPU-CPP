#!/bin/bash

# Update the package repository
sudo apt-get update

# Install essential packages
sudo apt-get install build-essential
# The build-essential package contains the necessary tools (e.g., GCC compiler) and libraries required for building software.

# Install OpenGL and GLUT
sudo apt-get install freeglut3 freeglut3-dev
# The freeglut3 package provides an open-source alternative to the OpenGL Utility Toolkit (GLUT), which is a library for creating OpenGL applications.
# The freeglut3-dev package contains the development files (header files and libraries) for freeglut3.

# Install additional libraries and dependencies
sudo apt-get install binutils-gold
# The binutils-gold package provides the Gold linker, which is a faster replacement for the default GNU linker (ld).
# It can improve the linking speed of large applications.

sudo apt-get install g++ cmake
# The g++ package is the GNU C++ compiler, which is required for compiling C++ code.
# The cmake package is a cross-platform build system that is used for configuring, building, and testing software.

sudo apt-get install mesa-common-dev mesa-utils
# The mesa-common-dev package provides the Mesa 3D graphics library, which is an open-source implementation of the OpenGL specification.
# It includes header files and development files necessary for compiling OpenGL applications.
# The mesa-utils package includes various utilities for interacting with the Mesa graphics drivers, such as glxinfo.

sudo apt-get install libglew-dev libglew1.5-dev libglm-dev
# The libglew-dev package contains the development files for the OpenGL Extension Wrangler Library (GLEW).
# GLEW is a cross-platform open-source C/C++ extension loading library that provides access to OpenGL extensions.
# The libglew1.5-dev package is a specific version of libglew-dev.
# The libglm-dev package provides the GLM library, which is a mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.

# Check OpenGL information
glxinfo | grep OpenGL
# The glxinfo command displays information about the OpenGL implementation and the available OpenGL extensions.
# The grep command is used to filter the output and only display lines containing the string "OpenGL".

