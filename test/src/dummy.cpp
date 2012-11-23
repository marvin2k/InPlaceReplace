#include "dummy.h"
#include <iostream>

using namespace test;
using namespace std;

using std::endl;

typedef struct
{
    int mFirst;
    int mSecond;
    int noTouch;
} myStruct;

void Person::set_name()
{
    std::cout << "bloa" << endl;

    myStruct* test = new myStruct;

    if (test->noTouch == 1) test->mSecond = 1;

    int copy = test->mFirst + test->mSecond;
    copy++;

    return;
}

void test::Person::get_name()
{
}

int test::Person::getVar(int mVar)
{
    return mVar*6;
}
