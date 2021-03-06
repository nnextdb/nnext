
## Build From Source
This guide for standard support releases of Ubuntu, Debian, and Linux Mint and will provide a local, non-system installation of FFmpeg with several external libraries.

> Note: NNext is working on making the nnext-server be part part of the Ubuntu packages and so that it can be installed via `apt-get install nnext`. You may still wish to compile if you want the latest version, experience a bug, or want to customize your build, and it will not interfere with the ffmpeg package in the repository.

## Build system.
In the C++ world, there's no "standard" build system that would work for in all supported
use cases and on all supported platforms. Therefore, NNext supports the most popular, major build system, `cmake`
which
should satisfy most users.

## Method 1 - Easier 🛝
Use Pre-build docker image for development purposes.
### 🚧 WIP 🚧

## Method 2 - Harder 🧗🏾‍♂️
### Step 1: Install cmake
You need version 3.19 or later of `cmake`. Install it and other dependencies by following these instructions:

* Linux
```shell
sudo apt install -y build-essential \
  autoconf libtool pkg-config libz-dev cmake
```

* macOS:
```shell
brew install cmake
```
For general cmake installation instructions, [see Installing CMake](https://cmake.org/install).

Check the version of `cmake:`
```shell
cmake --version
cmake version 3.19.6
```

### Step 2: Clone the repo
Clone the grpc repo and its submodules. Note how the submodule depth is specified to the latest version to minimix
code versioning issues.

```shell
git clone --recurse-submodules --depth 1 --shallow-submodules https://github.com/nnextai/nnext
```

Optionally, you can specify the exact version of NNext to build a git branch.
```shell
NNEXT_VERSION=v0.0.1
git clone --recurse-submodules -b $NNEXT_VERSION--depth 1 --shallow-submodules https://github.com/nnextai/nnext
```

### Step 3: Build gRPC

The steps in the section explain how to build and locally install gRPC and Protocol Buffers using cmake. Quick start
instructions explaining how to build and run simple gRPC programs can be found
[on grpc's website here](https://grpc.io/docs/languages/cpp/quickstart/).

##### Setup

Choose a directory to hold locally installed packages. This page assumes that
the environment variable `GRPC_INSTALL_DIR` holds this directory path. For example:

```shell
export GRPC_INSTALL_DIR=/usr/local/grpc
```

Ensure that the directory exists:

```shell
mkdir -p GRPC_INSTALL_DIR
```

Add the local bin folder to your path variable, for example:

```shell
export PATH="GRPC_INSTALL_DIR/bin:$PATH"
```

Clone the grpc repo

> ⚠️ Important ⚠️
>
> gRPC strongly encourages you to install gRPC locally — using an appropriately set CMAKE_INSTALL_PREFIX — because
> there is no easy way to uninstall gRPC after you’ve installed it globally.


#### Build and locally install gRPC and Protocol Buffers
NNext leverages gRPC and Protocol Buffers for service definitions and data
serialization. Specifically, NNext uses proto3 for protocol deffinitions.

The following commands build and locally install gRPC and Protocol Buffers:

```shell
cd nnext/third_party/grpc
mkdir -p cmake/build

pushd cmake/build

cmake -DgRPC_INSTALL=ON \
-DgRPC_BUILD_TESTS=OFF \
-DCMAKE_INSTALL_PREFIX=$GRPC_INSTALL_DIR \
../..

make -j
make install
popd

cd ..
```

### Step 4: Build RocksDB
NNext uses RocksDB to persist data to disk.

First, ensure that you are in the correct subdirectory. The rocksdb submodule should be located in the third_party
directory `nnext/third_party`.
```
# nnext/third_party
cd rocksdb
```

Compile librocksdb.a, RocksDB static library. Compiles static library in release mode.
```shell
make static_lib
```

Detailed instructions for [building rocksDB can be found here](https://github.com/facebook/rocksdb/blob/main/INSTALL.md).

### Step 5: Build FAISS library
NNext uses Faiss to manage the nearest neigbour indexes and perform the ANN computations.

Detailed instructions on how to build faiss can be found on [it's install guide](https://github.com/facebookresearch/faiss/blob/main/INSTALL.md).

First, ensure that you are in the correct subdirectory. The faiss submodule should be located in the third_party
directory `nnext/third_party`
```
# nnext/third_party/grpc
cd faiss
```

#### Install intel MKL BLAS library.
Faiss strongly recommends using Intel MKL for best performance.
```shell
sudo apt-get install intel-mkl
```

```shell
cmake -B build . \
  -DFAISS_ENABLE_GPU=OFF \
  -DFAISS_ENABLE_PYTHON=OFF \
  -DBUILD_TESTING=OFF \
  -DBUILD_SHARED_LIBS=ON \
  -DCMAKE_BUILD_TYPE=Release
```

Run the make command using all your's system's vCPUs.

> ⚠️ This has the effect of
building fast at the risk of reducing your systems reponsivity.
```shell
make -C build -j faiss
```

To run the make command leaving some room for vCPU resource to be dedicated to
other user processes, run.
```shell
nproc

>  16
#Subtract 1 from your processor count and run the make command 
make -C build -j 15 faiss
```

Alternatively, use the following one-liner.
```shell
make -C . -j$((`nproc`-1)) faiss
```

The resulting`.so`file will be located in `faiss/libfaiss.so`

If all goes according to plan, you should now be able to build NNext.

### Step 6: Build NNext
Finally the step we've all be waiting for 🥁🥁. Build the nnext library!

First, ensure you are in the `nnext` directory. Then run

```shell
cmake .
```
followed by
```shell
make -C . -j$((`nproc`-1))
```

The `nnext` executable will be located in the top level directory. You can run it like so
```shell
export NNEXT_DATA_DIR=/var/lib/nnext/data
sudo mkdir -p $NNEXT_DATA_DIR

# Run it!
./nnext --data-dir $NNEXT_DATA_DIR --verbose --port 6040
```

### Troubleshooting 🛠
#### 1. Protoc mismatch.

This usually results when the version of protoc used to build the .proto files is different from that used to build
nnext. Ensure you are using the same version, preferably the one that resulted in the gRPC build step.

### Adding third party dependencies.
Adding a third party dependency involves using [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules).
To install submodule `module-dep`, add it into the `third_party` directory. Like so.
```shell
git submodule add --depth 1 https://github.com/repo/module-dep.git third_party/module-dep
```
NNext depends on the following submodules.
```shell
git submodule add --depth 1 https://github.com/facebookresearch/faiss.git third_party/faiss
git submodule add --depth 1 https://github.com/grpc/grpc.git third_party/grpc
git submodule add --depth 1 https://github.com/p-ranav/argparse.git third_party/argparse
git submodule add --depth 1 https://github.com/gabime/spdlog.git third_party/spdlog
git submodule add --depth 1 https://github.com/facebook/rocksdb third_party/rocksdb
git submodule add --depth 1 https://github.com/fmtlib/fmt third_party/fmt
```
