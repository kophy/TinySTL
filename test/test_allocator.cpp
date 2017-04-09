#include <iostream>
#include <cstdlib>
#include "allocator.hpp"
#include "list.hpp"
#include "vector.hpp"
#include "utils.hpp"

#include <catch.hpp>

using namespace TinySTL;

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

    SECTION("only List") {
        Allocator<List<int>> alloc;
        List<int> *p = alloc.allocate(10);
        CHECK(p != nullptr);
        alloc.construct(p, 10);
        for (int i = 0; i < 10; ++i)
            CHECK(p[i].empty());
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

    SECTION("class with const member") {
        Allocator<Pair<int, int>> alloc;
        Pair<int, int> *p = alloc.allocate(5);
        alloc.construct(p, 5, 1, 2);
        for (int i = 0; i < 5; ++i) {
            CHECK(p[i].first == 1);
            CHECK(p[i].second == 2);
        }
    }
}
