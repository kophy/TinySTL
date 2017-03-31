#include <cstdlib>
#include "list.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using TinySTL::List;

TEST_CASE("front and back") {
    SECTION("empty list") {
        List<int> l;
        CHECK_THROWS_AS(l.front(), std::out_of_range);
        CHECK_THROWS_AS(l.back(), std::out_of_range);
    }
}

TEST_CASE("push front") {
    SECTION("push 1 ~ 5 from front") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_front(i);
        CHECK(l.front() == 4);
        CHECK(l.back() == 0);
    }
}

TEST_CASE("pop front") {
    SECTION("empty list") {
        List<int> l;
        CHECK_THROWS_AS(l.pop_front(), std::out_of_range);
    }

    SECTION("not empty list") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_front(i);
        l.pop_front();
        CHECK(l.front() == 3);
    }
}

TEST_CASE("push_back") {
    SECTION("push 1 ~ 5 from back") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(i);
        CHECK(l.front() == 0);
        CHECK(l.back() == 4);
    }
}

TEST_CASE("") {

}

TEST_CASE("pop back") {

}

TEST_CASE("clear") {
    SECTION("clear a list") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(i);
        CHECK(l.size() == 5);
        l.clear();
        CHECK(l.size() == 0);
    }
}
