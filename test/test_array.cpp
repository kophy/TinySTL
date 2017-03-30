#include <cstdlib>
#include "array.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using TinySTL::Array;

TEST_CASE("at") {
    Array<int, 10> arr;

    SECTION("in bound") {
        arr.at(2) = 3;
        CHECK(arr.at(2) == 3);
    }

    SECTION("out of bound") {
        CHECK_THROWS_AS(arr.at(-1), std::out_of_range);
        CHECK_THROWS_AS(arr.at(11), std::out_of_range);
    }
}

TEST_CASE("operator []") {
    Array<int, 10> arr;

    SECTION("in bound") {
        arr[2] = 3;
        CHECK(arr[2] == 3);
    }
}

TEST_CASE("empty") {
    SECTION("empty array") {
        Array<int, 0> arr;
        CHECK(arr.empty());
    }

    SECTION("not empty array") {
        Array<int, 3> arr;
        CHECK(!arr.empty());
    }
}

TEST_CASE("size") {
    SECTION("random array") {
        Array<int, 1337> arr;
        CHECK(arr.size() == 1337);
    }
}
