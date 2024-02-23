#include "ut.hpp"
#include "max-int-no-comp.h"

int main() {
    using namespace boost::ut;
    using mi_ns::max_int_nocmp;

#if defined (WIN32)
    cfg<override> ={.colors={.none="", .pass="", .fail=""}};
#endif

    "the only one"_test = [] {
        expect(max_int_nocmp(0, 0) == 0);
        expect(max_int_nocmp(-1, -1) == -1);
        expect(max_int_nocmp(1, 1) == 1);

        expect(max_int_nocmp(42, -42) == 42);
        expect(max_int_nocmp(-42, 42) == 42);

        expect(max_int_nocmp(8, 9) == 9);
        expect(max_int_nocmp(9, 8) == 9);

        expect(max_int_nocmp(-8, -9) == -8);
        expect(max_int_nocmp(-9, -8) == -8);

        expect(max_int_nocmp(-0x7ffffffe, -0x7fffffff) == -0x7ffffffe);
        expect(max_int_nocmp(-0x7fffffff, -0x7ffffffe) == -0x7ffffffe);

        expect(max_int_nocmp(0x7ffffffe, 0x7fffffff) == 0x7fffffff);
        expect(max_int_nocmp(0x7fffffff, 0x7ffffffe) == 0x7fffffff);

        expect(max_int_nocmp(0x7ffffffe, -0x7fffffff) == 0x7ffffffe);
        expect(max_int_nocmp(-0x7fffffff, 0x7ffffffe) == 0x7ffffffe);

        expect(max_int_nocmp(0x7fffffff, -0x7fffffff) == 0x7fffffff);
        expect(max_int_nocmp(-0x7fffffff, 0x7fffffff) == 0x7fffffff);

        expect(max_int_nocmp(-0x7ffffffe, 0x7fffffff) == 0x7fffffff);
        expect(max_int_nocmp(0x7fffffff, -0x7ffffffe) == 0x7fffffff);
    };
}
