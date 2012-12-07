#!/bin/bash

source env.sh

make -C test

git branch -D temp

./complex_example.py test/build/x86_64-linux-gnu/compile_commands.json test tester

git checkout temp
make -C test
git checkout private
