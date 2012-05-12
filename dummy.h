#ifndef DUMMY_H
#define DUMMY_H

namespace horse { class Bar; };

namespace test
{
    class Person {
        public:
            void set_name();
            void get_name();
        private:
            int hairs;
        /* friend: */
        /*     foo::Bar; */
    };
};

#endif/*DUMMY_H*/
