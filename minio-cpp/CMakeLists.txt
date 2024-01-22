# MinIO C++ Library for Amazon S3 Compatible Cloud Storage
# Copyright 2021 MinIO, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

project(miniocpp)

cmake_minimum_required(VERSION 3.10)

macro(set_globals)
  set(CMAKE_BUILD_TYPE_INIT Release)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} --coverage")
  set(CMAKE_EXE_LINKER_FLAGS_COVERAGE "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage")
  set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} --coverage")
  set(CMAKE_MODULE_LINKER_FLAGS_COVERAGE "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} --coverage")
endmacro()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# prohibit in-source-builds
IF (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
  MESSAGE(STATUS "In-source-builds are not allowed")
  MESSAGE(STATUS "Clean your source directory (e.g. delete the CMakeCache.txt file)")
  MESSAGE(FATAL_ERROR "Please create a separate build directory and call CMake again")
ENDIF (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})

# Look for required libraries
SET(requiredlibs)

IF(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Werror")
  IF(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8.0 AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0 AND NOT MINGW)
    list(APPEND requiredlibs stdc++fs)
  ENDIF()
ENDIF()

set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
message(STATUS "PKG_CONFIG_PATH:$ENV{PKG_CONFIG_PATH}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(CURL REQUIRED IMPORTED_TARGET libcurl)
pkg_check_modules(CURLPP REQUIRED IMPORTED_TARGET curlpp)
pkg_check_modules(PUGIXML REQUIRED IMPORTED_TARGET pugixml)
pkg_check_modules(INIH REQUIRED IMPORTED_TARGET inih)
pkg_check_modules(INIREADER REQUIRED IMPORTED_TARGET INIReader)
pkg_check_modules(SSL REQUIRED IMPORTED_TARGET libssl)
pkg_check_modules(OPENSSL REQUIRED IMPORTED_TARGET openssl)
pkg_check_modules(CRYPTO REQUIRED IMPORTED_TARGET libcrypto)
pkg_check_modules(ZLIB REQUIRED IMPORTED_TARGET zlib)

list(APPEND requiredlibs PkgConfig::CURL)
list(APPEND requiredlibs PkgConfig::CURLPP)
list(APPEND requiredlibs PkgConfig::PUGIXML)
list(APPEND requiredlibs PkgConfig::INIH)
list(APPEND requiredlibs PkgConfig::INIREADER)
list(APPEND requiredlibs PkgConfig::PUGIXML)
list(APPEND requiredlibs PkgConfig::OPENSSL)

message(STATUS "Found required libs: ${requiredlibs}")

INCLUDE (CheckIncludeFiles)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(MINIOCPP_MAJOR_VERSION "0")
SET(MINIOCPP_MINOR_VERSION "1")
SET(MINIOCPP_PATCH_VERSION "0")

include_directories(include/miniocpp)

add_subdirectory(include/miniocpp)
add_subdirectory(src)

set(S3_LIBS ${requiredlibs})