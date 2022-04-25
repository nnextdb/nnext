# Contributing to NNext

We want to make contributing to this project as easy and transparent as
possible.

## Our Development Process

We mainly develop NNext internally. Sometimes, we will sync the
github version of nnext with the internal state.

## Issues

We use GitHub issues to track public bugs. Please ensure your description is
clear and has sufficient instructions to be able to reproduce the issue.

## Coding Style

* 4 or 2 spaces for indentation in C++ (no tabs)
* 80 character line length (both for C++ and Python)
* C++ language level: C++11

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

## Pull Requests

We welcome pull requests that add significant value to NNext. If you plan to do
a major development and contribute it back to NNext, please contact us first before
putting too much effort into it.

1. Fork the repo and create your branch from `main`.
2. If you've added code that should be tested, add tests.
3. If you've changed APIs, update the documentation.
4. Ensure the test suite passes.
5. Make sure your code lints.

Internally, there is a test suite for nnext, and we need to run
all changes through it.

## License

By contributing to NNext, you agree that your contributions will be licensed
under the LICENSE file in the root directory of this source tree.
