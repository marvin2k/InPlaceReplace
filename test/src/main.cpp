#include <iostream>

#include "bar.h"
#include "dummy.h"

using test::Person;

int main(int argc, char const *argv[])
{
    Person test;
    foo::Bar var(&test);

    Person* p = new Person();

    std::cout << "first: " << var.getVar(7) << " second: " << test.getVar(7) << " third: " << p->getVar(7) << "\n";

    return 0;
}
