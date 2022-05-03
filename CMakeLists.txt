cmake_minimum_required(VERSION 3.7...3.23)

#If CMake version is less than 3.12, the if block will be true, and the policy will be set to the current CMake version.
# If CMake is 3.12 or higher, the if block will be false, but the new syntax in cmake_minimum_required will be
# respected and this will continue to work properly!
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(nnext VERSION 0.0.12
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

# Without --enable-new-dtags, you'll just set the RPATH flag, which is probably not what you want. With
# --enable-new-dtags, you'll set both RPATH and RUNPATH to the same value.
SET(CMAKE_EXE_LINKER_FLAGS  "-Wl,--enable-new-dtags")

# Runpaths to search for shared libraries.
set(RUNPATHS
        /usr/lib/nnext/third_party
        /usr/lib/nnext/x86_64-linux-gnu
        /usr/lib/nnext/intel_mkl
        $ORIGIN/third_party/faiss/build/faiss
        ${CMAKE_CURRENT_LIST_DIR}/third_party/faiss/build/faiss)
string(JOIN : RUNPATHS ${RUNPATHS})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS},-rpath,${RUNPATHS}")


# Skip the full RPATH for the build tree. RPATHs will be hardcoded into the nnext
# executable which results in developer's directories being set in the RUNPATH
# unnecessarily.
SET(CMAKE_SKIP_BUILD_RPATH TRUE)

message(DEBUG, "cxx flags ${CMAKE_CXX_FLAGS}")
message(DEBUG, "linker flags ${CMAKE_EXE_LINKER_FLAGS}")

find_package(Git)

add_subdirectory(protos)

if (DEFINED ENV{GRPC_INSTALL_DIR})
    MESSAGE(STATUS "Using gRPC install dir [env-var GRPC_INSTALL_DIR]  $ENV{GRPC_INSTALL_DIR}.")
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

# Here is the important line:
find_library(lz4_LIB lz4 REQUIRED)
find_library(zstd_LIB zstd REQUIRED)

# During build, find and link to faiss in the third_party directory. During
# installation using debian-package manager, copy the location of libfaiss.so
# to /usr/lib/nnext/x86_64-linux-gnu/third_party and link to it.
set(faiss_BUILD_PATH "${CMAKE_CURRENT_LIST_DIR}/third_party/faiss/build/faiss")
find_library(faiss_LIB faiss
        HINTS ${faiss_BUILD_PATH}
        REQUIRED)

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(ZLIB REQUIRED)
FIND_PACKAGE(BZip2 REQUIRED)

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
        ZLIB::ZLIB
        BZip2::BZip2
        lz4
        zstd
        Threads::Threads)

