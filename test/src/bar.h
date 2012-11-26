#ifndef BAR_H
#define BAR_H

#include "dummy.h"

namespace repretest
{
    struct blabla
    {
        int mId;
        int mTime;
    };

    struct blupp
    {
        struct blabla mBase;

        int bla;
        float mFloater;
        int mmm;
    };
}

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

            int getId() { return test.mBase.mId; };

            struct repretest::blupp test;
    };
}

#endif/*BAR_H*/
