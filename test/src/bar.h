#ifndef BAR_H
#define BAR_H

#include "dummy.h"

struct blupp
{
    int bla;
    float mFloater;
    int mmm;
};

namespace foo
{
    class Bar : public test::Person
    {
        public:
            Bar(test::Person* parent);
            virtual int getVar(int mVar);

        private:
            test::Person* mParent;
            int mBase;

            struct blupp test;
    };
}

#endif/*BAR_H*/
