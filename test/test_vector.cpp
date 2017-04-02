#include <cstdlib>
#include "vector.hpp"

#include "catch.hpp"

using TinySTL::Vector;

TEST_CASE("capacity") {
    SECTION("empty vector") {
        Vector<int> v;
        CHECK(v.empty());
        CHECK(v.size() == 0);
    }

    SECTION("not empty vector") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(i);
        CHECK(v.size() == 5);
    }
}

TEST_CASE("element access") {
    SECTION("empty vector") {
        Vector<int> v;
        CHECK_THROWS_AS(v.front(), std::out_of_range);
        CHECK_THROWS_AS(v.back(), std::out_of_range);
        CHECK_THROWS_AS(v[0], std::out_of_range);
    }

    SECTION("not empty vector: front and back") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(i);
        CHECK(v.front() == 0);
        CHECK(v.back() == 4);
        v.pop_back();
        CHECK(v.back() == 3);
    }

    SECTION("not empty vector: []") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(i);
        for (int i = 0; i < 5; ++i)
            CHECK(v[i] == i);
    }
}
