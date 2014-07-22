#!/bin/bash

# also needed to actually compile all this using clang (better template error
# messages)

export PATH=$HOME/llvm.install/bin:$PATH
export LD_LIBRARY_PATH=$HOME/llvm.install/lib:$LD_LIBRARY_PATH

export CC=$HOME/llvm.install/bin/clang
export CXX=$HOME/llvm.install/bin/clang++
