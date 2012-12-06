
all: restore cpp execute

restore:
	git checkout -- test

cpp:
	make -C cpp

# we care to reset the test-dir, calls the InPlaceReplace binary and displays the diff
execute: test restore
	./cpp/build/x86_64-unknown-linux-gnu/InPlaceReplace test/build/x86_64-unknown-linux-gnu test/src/bar.cpp
	git diff test

test:
	make -C test

clean: restore
	make -C cpp distclean
	make -C test distclean

.PHONY: cpp execute test clean
