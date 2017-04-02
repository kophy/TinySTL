#include <cstdlib>
#include "utils.hpp"

#include "catch.hpp"

using TinySTL::Pair;
using TinySTL::MakePair;
using TinySTL::Less;
using TinySTL::Greater;

TEST_CASE("Pair") {
    SECTION("read") {
        Pair<int, char> p = MakePair(1, 'a');
        CHECK(p.first == 1);
        CHECK(p.second == 'a');
    }

    SECTION("write") {
        Pair<int, char> p;
        p.first = 1;
        p.second = 'a';
        CHECK(p.first == 1);
        CHECK(p.second == 'a');
    }
}

TEST_CASE("Compare") {
    SECTION("default compare function") {
        CHECK(TinySTL::Min(1, 2) == 1);
        CHECK(TinySTL::Max(1, 2) == 2);
        CHECK(TinySTL::Min('a', 'b') == 'a');
        CHECK(TinySTL::Max('a', 'b') == 'b');
    }

    SECTION("user-defined compare function") {
        CHECK(TinySTL::Min(1, 2, Greater<int>) == 2);
        CHECK(TinySTL::Max(1, 2, Greater<int>) == 1);
        CHECK(TinySTL::Min('a', 'b', Greater<char>) == 'b');
        CHECK(TinySTL::Max('a', 'b', Greater<char>) == 'a');
    }
}
