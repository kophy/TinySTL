#include <iostream>
#include <cstdlib>
#include "allocator.hpp"

#include <catch.hpp>

using TinySTL::Allocator;

class PlusOne {
    public:
        static unsigned int count;
        PlusOne() { ++count; }
        ~PlusOne() { --count; }
};

unsigned int PlusOne::count = 0;

TEST_CASE("everything together") {
    SECTION("int") {
        Allocator<int> alloc;
        int *p = alloc.allocate(10);
        CHECK(p != nullptr);
        p[2] = 17;
        CHECK(p[2] == 17);
    }

    SECTION("user defined class") {
        Allocator<PlusOne> alloc;
        PlusOne *p = alloc.allocate(10);
        CHECK(PlusOne::count == 0);
        alloc.construct(p, 10);
        CHECK(PlusOne::count == 10);
        alloc.destroy(p, 10);
        CHECK(PlusOne::count == 0);
    }
}
