#include <iostream>
#include <cstdlib>
#include "tree_set.hpp"
#include "vector.hpp"

#include <catch.hpp>

using namespace TinySTL;

TEST_CASE("capacity") {
    SECTION("empty tree set") {
        TreeSet<int> s;
        CHECK(s.empty());
    }

    SECTION("not empty tree set") {
        TreeSet<int> s;
        for (int i = 0; i < 5; ++i)
            s.insert(i);
        CHECK(s.size() == 5);
    }
}

TEST_CASE("insert, erase and clear") {
    SECTION("insert 1 ~ 5, erase 3") {
        TreeSet<int> s;
        for (int i = 0; i < 5; ++i)
            s.insert(i);
        for (int i = 0; i < 5; ++i)
            CHECK(s.count(i) == 1);
        s.erase(3);
        CHECK(s.count(3) == 0);
        s.clear();
        CHECK(s.empty());
    }
}

TEST_CASE("iterator") {
    SECTION("read") {
        TreeSet<int> s;
        int data[] = {7, 13, 17, 23, 47};
        for (int i = 0; i < 5; ++i)
            s.insert(data[i]);
        int i = 0;
        for (auto iter = s.begin(); iter != s.end(); ++iter)
            CHECK(*iter == data[i++]);
        CHECK(i == 5);
    }

    SECTION("write") {
        TreeSet<int> s;
        for (int i = 0; i < 10; ++i)
            s.insert(i);
        auto iter = s.begin();
        // CHECK_THROWS(*iter = 8); -- this will cause error in compiling stage
    }
}

TEST_CASE("reverse iterator") {
    SECTION("read") {
        TreeSet<int> s;
        int data[] = {7, 13, 17, 23, 47};
        for (int i = 0; i < 5; ++i)
            s.insert(data[i]);
        int i = 5;
        for (auto iter = s.rbegin(); iter != s.rend(); ++iter)
            CHECK(*iter == data[--i]);
        CHECK(i == 0);
    }

    SECTION("write") {
        TreeSet<int> s;
        for (int i = 0; i < 10; ++i)
            s.insert(i);
        auto iter = s.rbegin();
        // CHECK_THROWS(*iter = 8); -- this will cause error in compiling stage
    }
}

TEST_CASE("find") {
    TreeSet<int> s;
    for (int i = 0; i < 5; ++i)
        s.insert(i);

    SECTION("element in tree set") {
        auto iter = s.find(3);
        CHECK(*iter == 3);
    }

    SECTION("element not in tree set") {
        auto iter = s.find(7);
        CHECK(iter == s.end());
    }
}
