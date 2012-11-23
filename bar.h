#ifndef BAR_H
#define BAR_H

#include "dummy.h"

struct blupp
{
    int bla;
    float mFloat;
    int mmm;
};

namespace foo
{
    class Bar : public test::Person
    {
            Bar(test::Person* parent);
        private:
            test::Person* mParent;
            int mBase;

            struct blupp test;
    };
}

#endif/*BAR_H*/
