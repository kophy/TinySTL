#include <cstdlib>
#include "array.hpp"

#include <catch.hpp>

using TinySTL::Array;

TEST_CASE("at") {
    SECTION("in bound") {
        Array<int, 10> arr;
        arr.at(2) = 3;
        CHECK(arr.at(2) == 3);
    }

    SECTION("out of bound") {
        Array<int, 10> arr;
        CHECK_THROWS_AS(arr.at(-1), std::out_of_range);
        CHECK_THROWS_AS(arr.at(11), std::out_of_range);
    }
}

TEST_CASE("operator []") {
    SECTION("in bound") {
        Array<int, 10> arr;
        arr[2] = 3;
        CHECK(arr[2] == 3);
    }
}

TEST_CASE("front and back") {
    SECTION("empty array") {
        Array<int, 0> arr;
        CHECK_THROWS_AS(arr.front(), std::out_of_range);
        CHECK_THROWS_AS(arr.back(), std::out_of_range);
    }

    SECTION("not empty array") {
        Array<int, 5> arr;
        for (int i = 0; i < 5; ++i)
            arr[i] = i;
        CHECK(arr.front() == 0);
        CHECK(arr.back() == 4);
    }
}

TEST_CASE("iterator") {
    SECTION("empty array") {
        Array<int, 0> arr;
        CHECK(arr.begin() == arr.end());
    }

    SECTION("not empty array") {
        Array<int, 5> arr;
        CHECK(arr.begin() == arr.begin());
        CHECK(arr.end() == arr.end());
    }

    SECTION("* and ++") {
        int data[] = {7, 11, 23, 41, 73};
        int i;
        Array<int, 5> arr;

        i = 0;
        for (auto iter = arr.begin(); iter != arr.end(); ++iter)
            *iter = data[i++];
        CHECK(i == 5);
        i = 0;
        for (auto iter = arr.begin(); iter != arr.end(); iter++)
            CHECK(*iter == data[i++]);
        CHECK(i == 5);
    }
}

TEST_CASE("reverse iterator") {
    SECTION("empty array") {
        Array<int, 0> arr;
        CHECK(arr.rbegin() == arr.rend());
    }

    SECTION("not empty array") {
        Array<int, 5> arr;
        CHECK(arr.rbegin() == arr.rbegin());
        CHECK(arr.rend() == arr.rend());
    }

    SECTION("* and ++") {
        int data[] = {7, 11, 23, 41, 73};
        int i;
        Array<int, 5> arr;

        i = 5;
        for (auto iter = arr.rbegin(); iter != arr.rend(); ++iter)
            *iter = data[--i];
        CHECK(i == 0);
        i = 5;
        for (auto iter = arr.rbegin(); iter != arr.rend(); iter++)
            CHECK(*iter == data[--i]);
        CHECK(i == 0);
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

TEST_CASE("fill") {
    SECTION("fill with random value") {
        int d = rand();
        Array<int, 5> arr;
        arr.fill(d);
        for (int i = 0; i < 5; ++i)
            CHECK(arr[i] == d);
    }
}

TEST_CASE("swap") {
    SECTION("swap two arrays") {
        Array<int, 5> arr1, arr2;
        for (int i = 0; i < 5; ++i) {
            arr1[i] = i;
            arr2[i] = 4 - i;
        }
        arr1.swap(arr2);
        for (int i = 0; i < 5; ++i) {
            CHECK(arr1[i] == 4 - i);
            CHECK(arr2[i] == i);
        }
    }
}
