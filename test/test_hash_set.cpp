#include <cstdlib>
#include "hash_set.hpp"
#include "vector.hpp"

#include <catch.hpp>

using namespace TinySTL;

TEST_CASE("capacity") {
    SECTION("empty hash set") {
        HashSet<int> s;
        CHECK(s.empty());
    }

    SECTION("not empty hash set") {
        HashSet<int> s;
        for (int i = 0; i < 5; ++i)
            s.insert(i);
        CHECK(s.size() == 5);
    }
}

TEST_CASE("insert, erase and clear") {
    SECTION("insert 1 ~ 5, erase 3") {
        HashSet<int> s;
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
        HashSet<int> s;
        Vector<int> data;
        for (int i = 0; i < 10; ++i) {
            s.insert(i);
            data.push_back(i);
        }
        int i = 0;
        for (auto iter = s.begin(); iter != s.end(); ++iter) {
            CHECK(Count(data.begin(), data.end(), *iter) == 1);
            ++i;
        }
        CHECK(i == 10);
    }

    SECTION("write") {
        HashSet<int> s;
        for (int i = 0; i < 10; ++i)
            s.insert(i);
        auto iter = s.begin();
        // CHECK_THROWS(*iter = 8); -- this will cause error in compiling stage
    }
}

TEST_CASE("find") {
    HashSet<int> s;
    for (int i = 0; i < 5; ++i)
        s.insert(i);

    SECTION("element in hash set") {
        auto iter = s.find(3);
        CHECK(*iter == 3);
    }

    SECTION("element not in hash set") {
        auto iter = s.find(7);
        CHECK(iter == s.end());
    }
}
