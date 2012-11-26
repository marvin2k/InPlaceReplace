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
    static int myIntmVar = 0;

    int notUsed = test.mBase.mId + test.mBase.mTime;
    notUsed++;

    return myIntmVar + mVar*7;
}

