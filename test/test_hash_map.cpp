#include <cstdlib>
#include "hash_map.hpp"
#include "vector.hpp"

#include <catch.hpp>

using namespace TinySTL;

TEST_CASE("capacity") {
    SECTION("empty hash map") {
        HashMap<int, int> m;
        CHECK(m.empty());
    }

    SECTION("not empty hash map") {
        HashMap<int, int> m;
        for (int i = 0; i < 5; ++i)
            m.insert(i, 2 * i);
        CHECK(m.size() == 5);
        m.erase(1);
        CHECK(m.size() == 4);
        m.clear();
        CHECK(m.empty());
    }
}

TEST_CASE("count") {
    SECTION("insert 0 ~ 4") {
        HashMap<int, int> m;
        for (int i = 0; i < 5; ++i)
            m.insert(i, 2 * i);
        for (int i = 0; i < 5; ++i)
            CHECK(m.count(i) == 1);
        CHECK(m.count(7) == 0);
    }
}

TEST_CASE("iterator") {
    int data[] = {7, 13, 17, 23, 103};
    HashMap<int, int> m;
    for (int i = 0; i < 5; ++i)
        m.insert(i, data[i]);

    SECTION("read with *") {
        int i = 0;
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            CHECK((*iter).first == i);
            CHECK((*iter).second == data[i]);
            ++i;
        }
        CHECK(i == 5);
    }

    SECTION("write with *") {
        for (auto iter = m.begin(); iter != m.end(); ++iter)
            (*iter).second = (*iter).second * 2;
        int i = 0;
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            CHECK((*iter).first == i);
            CHECK((*iter).second == data[i] * 2);
            ++i;
        }
        CHECK(i == 5);
    }

    SECTION("read with ->") {
        int i = 0;
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            CHECK(iter->first == i);
            CHECK(iter->second == data[i]);
            ++i;
        }
        CHECK(i == 5);
    }

    SECTION("write with ->") {
        for (auto iter = m.begin(); iter != m.end(); ++iter)
            iter->second = iter->second * 2;
        int i = 0;
        for (auto iter = m.begin(); iter != m.end(); ++iter) {
            CHECK(iter->first == i);
            CHECK(iter->second == data[i] * 2);
            ++i;
        }
        CHECK(i == 5);
    }
}

TEST_CASE("find") {
    int data[] = {7, 13, 17, 23, 103};
    HashMap<int, int> m;
    for (int i = 0; i < 5; ++i)
        m.insert(i, data[i]);

    SECTION("element in hash map") {
        auto iter = m.find(3);
        CHECK(iter->second == data[3]);
    }

    SECTION("element not in hash map") {
        auto iter = m.find(7);
        CHECK(iter == m.end());
    }
}

TEST_CASE("[]") {
    SECTION("insert and modify") {
        int data[] = {7, 13, 17, 23, 103};
        HashMap<int, int> m;
        for (int i = 0; i < 5; ++i)
            m[i] = data[i];
        CHECK(m.size() == 5);
        for (int i = 0; i < 5; ++i)
            CHECK(m[i] == data[i]);
        m[3] = m[3] * 2;
        CHECK(m[3] == data[3] * 2);
    }
}
