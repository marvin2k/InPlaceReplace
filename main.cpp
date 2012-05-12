//g++ main.cpp bar.cpp dummy.cpp -o dummy
//
#include "dummy.h"

// this is not catched
using test::Person;

int main()
{
    Person* p = new Person();

    return 0;
}
