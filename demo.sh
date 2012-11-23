#!/bin/bash

source env.sh

make -C test

./complex_example.py test/build/x86_64-linux-gnu/compile_commands.json test tester /home/mzenzes/InPlaceReplace

make -C test
