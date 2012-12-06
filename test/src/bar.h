#ifndef BAR_H
#define BAR_H

#include "dummy.h"

/* using namespaces just to avaid a too simple case */
namespace plotz
{
    /* this is the actual struct we will deal with */
    struct tree
    {
        int leaf;
        int trunk;
        double bird;
    };

    /* defines one of this structs */
    struct planet
    {
        /* here, we wanna rename "oak" */
        struct tree oak;

        /* visual clutter... */
        int sky;
        int beach;
        float sea;
    };
}

static struct plotz::planet mars;

namespace foo
{
    /* this class uses the struct-chain, where we have to rename stuff */
    class Bar
    {
        public:
            Bar();
            virtual int getSkyColor(int param);

        private:
            int tap;

            /* one of the occurences of "oak" -- has o be replaced */
            int getLeafs() { return earth.oak.leaf; };

            /* here, nothing should match */
            struct plotz::planet earth;
    };
}

#endif/*BAR_H*/
