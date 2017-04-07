#include <cstdlib>
#include "bitset.hpp"

#include <catch.hpp>

using TinySTL::Bitset;

TEST_CASE("everything together") {
    SECTION("size") {
        Bitset<5> b;
        CHECK(b.size() == 5);
    }

    SECTION("test, set and reset") {
        Bitset<5> b;
        b.set(1);
        CHECK(b.test(1));
        b.reset(1);
        CHECK(!b.test(1));
        CHECK_THROWS_AS(b.test(6), std::out_of_range);
        CHECK_THROWS_AS(b.set(6), std::out_of_range);
        CHECK_THROWS_AS(b.reset(6), std::out_of_range);
    }

    SECTION("any, none, all") {
        Bitset<2> b1(0), b2(2), b3(3);
        CHECK(b1.none());
        CHECK(b2.any());
        CHECK(b3.all());
    }

    SECTION("count") {
        Bitset<5> b1(0), b2(5);
        CHECK(b1.count() == 0);
        CHECK(b2.count() == 2);
    }

    SECTION("reference and []") {
        Bitset<3> b(1);
        CHECK(b[0]);
        CHECK(!b[1]);
        CHECK(!b[2]);
        b[1] = true;
        b[2] = b[0];
        b[0] = !b[0];
        CHECK(!b[0]);
        CHECK(b[1]);
        CHECK(b[2]);
    }

    SECTION("to_ulong") {
        Bitset<3> b(2);
        CHECK(b.to_ulong() == 2);
        b.set(2);
        CHECK(b.to_ulong() == 6);
    }
}
