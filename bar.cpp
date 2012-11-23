#include "bar.h"

using foo::Bar;
using test::Person;

Bar::Bar(test::Person* parent) :
    Person(),
    mParent(parent)
{
    test.mFloat = 7;
}

