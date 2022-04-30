cmake_minimum_required(VERSION 3.7...3.23)

#If CMake version is less than 3.12, the if block will be true, and the policy will be set to the current CMake version.
# If CMake is 3.12 or higher, the if block will be false, but the new syntax in cmake_minimum_required will be
# respected and this will continue to work properly!
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(nnext VERSION 0.0.11
        DESCRIPTION "NNext - A blazingly fast ⚡️ open-source NN vector search engine."
        HOMEPAGE_URL "https://nnext.ai"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)            # Enable c++23 standard
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror")

# RPATH Settings
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/RPATH-handling
# -----------------------------------------------------------------------
SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--enable-new-dtags")

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# the RPATH to be used when installing
set(CMAKE_INSTALL_RPATH "/lib/nnext/x86_64-linux-gnu")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# -----------------------------------------------------------------------

message(DEBUG, "cxx flags ${CMAKE_CXX_FLAGS}")
message(DEBUG, "linker flags ${CMAKE_EXE_LINKER_FLAGS}")

find_package(Git)

add_subdirectory(protos)

if (DEFINED ENV{GRPC_INSTALL_DIR})
    MESSAGE(STATUS "Using gRPC install dir [env-var GRPC_INSTALL_DIR]  $ENV{GRPC_INSTALL_DIRX}.")
else ()
    MESSAGE(FATAL_ERROR "GRPC_INSTALL_DIR env-var not specified")
endif ()

include_directories(
        third_party/spdlog/include
        third_party/rocksdb/include
        third_party/faiss
        third_party/argparse/include
        $ENV{GRPC_INSTALL_DIR}/include
)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp server.h server.cpp util.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(nnext ${SOURCE_FILES})


ADD_LIBRARY(RocksDB STATIC IMPORTED)
SET_TARGET_PROPERTIES(RocksDB PROPERTIES IMPORTED_LOCATION
        "${CMAKE_CURRENT_LIST_DIR}/third_party/rocksdb/librocksdb.a")

SET(faiss_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/faiss/build/faiss")
message(STATUS "${faiss_DIR}")

find_library(faiss_LIB
        NAMES faiss libfaiss
        HINTS "${faiss_DIR}")

if (NOT faiss_LIB)
    MESSAGE(FATAL_ERROR "faiss lib not found.")
else ()
    MESSAGE(STATUS "Using faiss lib ${faiss_LIB}")
endif ()

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(ZLIB REQUIRED)
FIND_PACKAGE(BZip2 REQUIRED)
find_library(/usr/lib/x86_64-linux-gnu/ lz4)
find_library(/usr/lib/x86_64-linux-gnu/ zstd)

FIND_PACKAGE(OpenMP)
if (NOT DEFINED OpenMP_CXX_FOUND)
    MESSAGE(FATAL_ERROR "OpenMP not found.")
else ()
    MESSAGE(STATUS "Using OpenMP version ${OpenMP_CXX_VERSION}")
endif ()

TARGET_LINK_LIBRARIES(nnext ${CMAKE_DL_LIBS} nnext_grpc_proto
        ${faiss_LIB}
        RocksDB
        OpenMP::OpenMP_CXX
        ZLIB::ZLIB BZip2::BZip2 lz4 zstd
        Threads::Threads)

