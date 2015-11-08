cmake_minimum_required (VERSION 2.6)
project (DroidSharpInterop)

if(NOT ANDROID)
	message(FATAL_ERROR "Building without the android toolchain is not supported")
elseif(NOT MONO_ROOT)
	message(WARNING "MONO_ROOT is not set")
endif()

set (DroidSharpInterop_VERSION_MAJOR 1)
set (DroidSharpInterop_VERSION_MINOR 0)

set(MONO_ROOT ${MONO_ROOT} CACHE PATH "")

set(CMAKE_FIND_ROOT_PATH_TEMP ${CMAKE_FIND_ROOT_PATH})
unset(CMAKE_FIND_ROOT_PATH)

find_path(MONO_INCLUDE_DIR
	mono/jit/jit.h
	HINTS
		${MONO_ROOT}
	PATH_SUFFIXES
		include/mono-2.0
		mono-2.0
		include)

find_library(MONO_LIBRARY
	NAMES
		monosgen-2.0
		mono-2.0
	HINTS
		${MONO_ROOT}/lib)

set(CMAKE_FIND_ROOT_PATH ${CMAKE_FIND_ROOT_PATH_TEMP})

find_package(Threads REQUIRED)

if(THREADS_HAVE_PTHREAD_ARG)
	set_property(TARGET DroidSharpInterop PROPERTY COMPILE_OPTIONS "-pthread")
	set_property(TARGET DroidSharpInterop PROPERTY INTERFACE_COMPILE_OPTIONS "-pthread")
endif()

include_directories("${PROJECT_SOURCE_DIR}/include" "${MONO_INCLUDE_DIR}")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

add_library(DroidSharpInterop SHARED "${SRC_DIR}/Interop.c")
target_link_libraries(DroidSharpInterop ${MONO_LIBRARY} "${CMAKE_THREAD_LIBS_INIT}" m log)
