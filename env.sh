#!/bin/bash

export LD_LIBRARY_PATH=$HOME/llvm.install/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$HOME/llvm.git/tools/clang/bindings/python/clang:$HOME/InPlaceReplace:$PYTHONPATH
