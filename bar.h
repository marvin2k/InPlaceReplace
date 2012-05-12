#ifndef BAR_H
#define BAR_H

#include "dummy.h"

namespace foo
{
    class Bar : public test::Person
    {
        Bar(test::Person* parent);
    private:
        test::Person* mParent;
    };
}

#endif/*BAR_H*/
