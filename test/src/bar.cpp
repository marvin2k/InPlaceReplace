#include "bar.h"

using foo::Bar;
using test::Person;

Bar::Bar()
{
    /* another place where the "oak" string should be found */
    earth.oak.trunk = -1;
}

int foo::Bar::getSkyColor(int param)
{
    /* really hard: two times in one line */
    int notUsed = earth.oak.leaf + earth.oak.trunk;

    /* a variable called oak, but no to be matched */
    const char* oak = "fooled you";

    mars.oak.bird = 1;

    return notUsed;
}

