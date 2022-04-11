cmake_minimum_required(VERSION 3.7...3.22)

#If CMake version is less than 3.12, the if block will be true, and the policy will be set to the current CMake version.
# If CMake is 3.12 or higher, the if block will be false, but the new syntax in cmake_minimum_required will be
# respected and this will continue to work properly!
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(nnext VERSION 0.0.1
        DESCRIPTION "NNext - A blazingly fast ⚡️ open-source NN vector search engine."
        HOMEPAGE_URL "https://nnext.ai"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)            # Enable c++23 standard
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
SET(CMAKE_CXX_FLAGS "-g -Wall -Werror")

message(STATUS, "${CMAKE_CXX_FLAGS}")

find_package(Git)

add_subdirectory(protos)

include_directories(
        lib/extern/spdlog/include/spdlog/include
        lib/extern/argparse/include/argparse/include
        lib/extern/rocksdb/include/rocksdb/include
        lib/extern/grpc/include/grpc-install/include
        lib/extern/faiss/include/faiss
        lib/extern/fmt/include/fmt-8.1.1/include
)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp server.h server.cpp util.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(nnext ${SOURCE_FILES})
add_subdirectory(lib/extern/spdlog)
#add_subdirectory(lib/extern/argparse)
add_subdirectory(lib/extern/rocksdb)




ADD_LIBRARY(RocksDB STATIC IMPORTED)
SET_TARGET_PROPERTIES(RocksDB PROPERTIES IMPORTED_LOCATION /home/peter/code/nnext/nnext/lib/extern/rocksdb/include/rocksdb/librocksdb.a)

ADD_LIBRARY(faiss STATIC IMPORTED)
SET_TARGET_PROPERTIES(faiss PROPERTIES IMPORTED_LOCATION
        /home/peter/code/nnext/nnext/lib/extern/faiss/include/faiss/faiss/libfaiss.so)

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(ZLIB)

TARGET_LINK_LIBRARIES(nnext ${CMAKE_DL_LIBS} nnext_grpc_proto faiss RocksDB Threads::Threads ZLIB::ZLIB   )

