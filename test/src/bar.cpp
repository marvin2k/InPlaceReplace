#include "bar.h"

using foo::Bar;
using test::Person;

Bar::Bar(test::Person* parent) :
    Person(),
    mParent(parent)
{
    test.mFloater = 7;
}

int foo::Bar::getVar(int mVar)
{
    static int myIntmVar;

    return mVar*7;
}

