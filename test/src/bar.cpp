#include "bar.h"

using foo::Bar;
using test::Person;

Bar::Bar(test::Person* parent) :
    Person(),
    mParent(parent)
{
    test.mFloat = 7;
}

int foo::Bar::getVar(int mVar)
{
    return mVar*7;
}

