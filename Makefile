# expects the name to be a directory inside a valid git repo, on which some tooling is done!
# for example UseCase is "$HOME/InPlaceReplace.git/UseCase" is inside one. this one.
VICTIM=UseCase

all: restore InPlaceReplace execute

restore:
	git checkout -- ${VICTIM}

InPlaceReplace:
	make -C InPlaceReplace

# we care to reset the test-dir, call the InPlaceReplace binary and display the diff
# attention, ugly hack using wildcard there...
execute: ${VICTIM} restore
	./InPlaceReplace/InPlaceReplace ${VICTIM}/build/* ${VICTIM}/src/bar.cpp
	git diff ${VICTIM}

${VICTIM}:
	${MAKE} -C ${VICTIM}

clean: restore
	${MAKE} -C InPlaceReplace distclean
	${MAKE} -C ${VICTIM} distclean

.PHONY: ${VICTIM} execute InPlaceReplace clean
