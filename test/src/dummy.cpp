#include "dummy.h"
#include <iostream>

using namespace test;
using namespace std;

using std::endl;

void Person::set_name()
{
    std::cout << "bloa" << endl;

    return;
}

void test::Person::get_name()
{
}

int test::Person::getVar(int mVar)
{
    return mVar*6;
}
