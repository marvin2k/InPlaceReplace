#!/bin/bash

# needed to actually compile all this using clang, and to use the python bindings.

export PATH=$HOME/llvm.install/bin:$PATH
export LD_LIBRARY_PATH=$HOME/llvm.install/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$HOME/llvm.git/tools/clang/bindings/python/clang:$PWD/python:$PYTHONPATH
