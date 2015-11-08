# DroidSharp-Interop

DroidSharp-Interop is a native helper library to load the Mono VM and execute managed code. It is required by the DroidSharp-Activity project to run any managed code.

## TL;DR

    cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/android.toolchain.cmake \
          -DANDROID_NDK=<ndk_path>                                        \
          -DMONO_ROOT=<mono_path>
          .
    make

This will compile the project for use with DroidSharp-Activity on the Android platform.

# Getting started

To get started you need the following tools and libraries downloaded and installed:
* [Android NDK](http://developer.android.com/ndk/downloads/index.html)
* [cmake](https://cmake.org)
* [Mono](https://github.com/mono/mono) - [Build scripts](https://github.com/DroidSharp/Build)

# Available Options

There are several options that can be passed to cmake to configure the build:
* ```CMAKE_TOOLCHAIN_FILE``` location of the cross-compile toolchain cmake file
* ```ANDROID_NDK``` location of the Android NDK (>= r5 required)
* ```MONO_ROOT``` location of the mono installation

# License

DroidSharp-Interop is copyrighted (C) by Zachariah Brown and licensed under the terms of LGPLv3.
