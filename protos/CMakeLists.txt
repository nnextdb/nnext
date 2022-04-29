cmake_minimum_required(VERSION 3.7...3.23)

#If CMake version is less than 3.12, the if block will be true, and the policy will be set to the current CMake version.
# If CMake is 3.12 or higher, the if block will be false, but the new syntax in cmake_minimum_required will be
# respected and this will continue to work properly!
if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif ()

project(NNext_proto C CXX)

message(DEBUG, "In module ${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 23)            # Enable c++23 standard
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

# Proto file
get_filename_component(nnext_proto "./main.proto" ABSOLUTE)
get_filename_component(nnext_proto_path "${nnext_proto}" PATH)

MESSAGE(DEBUG, "nnext_proto ${nnext_proto}")
MESSAGE(DEBUG, "nnext_proto_path ${nnext_proto_path}")

# Generated sources
set(nnext_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/main.pb.cc")
set(nnext_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/main.pb.h")
set(nnext_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/main.grpc.pb.cc")
set(nnext_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/main.grpc.pb.h")

if (DEFINED ENV{GRPC_INSTALL_DIR})
    MESSAGE(STATUS "Using gRPC install dir [env-var GRPC_INSTALL_DIR]  $ENV{GRPC_INSTALL_DIR}")
else ()
    MESSAGE(FATAL_ERROR "GRPC_INSTALL_DIR env-var not specified")
endif ()

find_program(_GRPC_CPP_PLUGIN_EXECUTABLE "$ENV{GRPC_INSTALL_DIR}/bin/grpc_cpp_plugin")
find_program(_PROTOBUF_PROTOC "$ENV{GRPC_INSTALL_DIR}/bin/protoc")
set(_REFLECTION "$ENV{GRPC_INSTALL_DIR}/lib/libgrpc++_reflection.a")

# Find gRPC and absl.
SET(gRPC_INSTALL_DIR $ENV{GRPC_INSTALL_DIR}/lib/cmake)
MESSAGE(STATUS, "gRPC install directory: ${gRPC_INSTALL_DIR}")


SET(Protobuf_DIR "third_party/grpc/cmake/build/third_party/protobuf/lib/cmake/protobuf")

FIND_PACKAGE(Protobuf CONFIG REQUIRED)


SET(absl_DIR ${gRPC_INSTALL_DIR}/absl)
FIND_PACKAGE(absl CONFIG REQUIRED)
message(STATUS "Using absl version ${absl_VERSION}")

SET(gRPC_DIR ${gRPC_INSTALL_DIR}/grpc)
FIND_PACKAGE(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC version ${gRPC_VERSION}")

SET(c-ares_DIR ${gRPC_INSTALL_DIR}/c-ares)
FIND_PACKAGE(c-ares CONFIG REQUIRED)
message(STATUS "Using c-ares version ${c-ares_VERSION}")


set(_GRPC_GRPCPP gRPC::grpc++)

if (NOT DEFINED Protobuf_FOUND)
    MESSAGE(FATAL_ERROR "You must set protobuf")
else ()
    MESSAGE(STATUS "Using protobuf version ${Protobuf_VERSION}")
endif ()

if (NOT DEFINED _PROTOBUF_PROTOC)
    MESSAGE(FATAL_ERROR "You must set _PROTOBUF_PROTOC variable")
else ()
    MESSAGE(STATUS "Using protoc compiler _PROTOBUF_PROTOC ${_PROTOBUF_PROTOC}")
endif ()


if (NOT DEFINED _GRPC_CPP_PLUGIN_EXECUTABLE)
    message(FATAL_ERROR "You must set _GRPC_CPP_PLUGIN_EXECUTABLE variable")
else ()
    MESSAGE(STATUS "Using protoc cpp compiler _GRPC_CPP_PLUGIN_EXECUTABLE ${_GRPC_CPP_PLUGIN_EXECUTABLE}")
endif ()


add_custom_command(
        OUTPUT "${nnext_proto_srcs}" "${nnext_proto_hdrs}" "${nnext_grpc_srcs}" "${nnext_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS    --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
                --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
                -I "${nnext_proto_path}"
                --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
                "${nnext_proto}"
        DEPENDS "${nnext_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

message(STATUS, ${_PROTOBUF_PROTOC})
message(STATUS, ${nnext_grpc_srcs})
message(STATUS, ${nnext_grpc_hdrs})
message(STATUS, ${nnext_proto_srcs})
message(STATUS, ${nnext_proto_hdrs})

add_library(nnext_grpc_proto
        ${nnext_grpc_srcs}
        ${nnext_grpc_hdrs}
        ${nnext_proto_srcs}
        ${nnext_proto_hdrs})

message(STATUS "Protobuf_DIR=${Protobuf_DIR}")

FIND_PACKAGE(Protobuf CONFIG REQUIRED)
FIND_PACKAGE(Protobuf CONFIG REQUIRED)
message(STATUS "Protobuf_DIR=${Protobuf_DIR}")
message(STATUS "Protobuf_LIBRARY=${Protobuf_LIBRARY}")
target_link_libraries(nnext_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${Protobuf_LIBRARY})