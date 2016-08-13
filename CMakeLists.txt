cmake_minimum_required(VERSION 2.8)

project(posa-project)

message("CMake system name: ${CMAKE_SYSTEM_NAME}")

if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
message(FATAL_ERROR "CMake generation is not allowed within the source directory!
Remove the CMakeCache.txt file and try again from another folder, e.g.:

   rm CMakeCache.txt
   mkdir build
   cd build
   cmake ..
")
endif()

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

if (DEBUG_MODE)
add_definitions(-DPOSA_DEBUG=1)
set(CMAKE_BUILD_TYPE "Debug")
        if(NOT WIN32)
                add_definitions(-g)
        endif()
else()
        if(NOT WIN32)
                add_definitions(-O3)
        endif()
endif()
if (NOT WIN32)
	add_definitions(-std=c99 -fPIC)
endif()

set(POSA_INCLUDE_DIRS "${posa-project_SOURCE_DIR}/src/lib/include/" "${posa-project_BINARY_DIR}/src/lib/include")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        set(POSA_LIBRARY "${posa-project_BINARY_DIR}/src/lib/libposa.dylib")
else()
        set(POSA_LIBRARY "${posa-project_BINARY_DIR}/src/lib/libposa.so")
endif()

add_subdirectory(src)
