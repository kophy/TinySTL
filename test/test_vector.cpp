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

TEST_CASE("iterator") {
    SECTION("read") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(i);
        int i = 0;
        for (auto iter = v.begin(); iter != v.end(); ++iter)
            CHECK(*iter == i++);
        CHECK(i == 5);
    }

    SECTION("write") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(i);
        for (auto iter = v.begin(); iter != v.end(); ++iter)
            *iter = (*iter) * 2;
        int i = 0;
        for (auto iter = v.begin(); iter != v.end(); iter++) {
            CHECK(*iter == i * 2);
            ++i;
        }
    }
}

TEST_CASE("reverse iterator") {
    SECTION("read") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(i);
        int i = 5;
        for (auto iter = v.rbegin(); iter != v.rend(); ++iter)
            CHECK(*iter == --i);
        CHECK(i == 0);
    }

    SECTION("write") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(i);
        for (auto iter = v.rbegin(); iter != v.rend(); ++iter)
            *iter = (*iter) * 2;
        int i = 5;
        for (auto iter = v.rbegin(); iter != v.rend(); iter++) {
            --i;
            CHECK(*iter == i * 2);
        }
        CHECK(i == 0);
    }
}

TEST_CASE("insert") {
    SECTION("front") {
        Vector<int> v;
        v.insert(v.begin(), 7);
        CHECK(v.front() == 7);
        CHECK(v.back() == 7);
    }

    SECTION("back") {
        Vector<int> v;
        v.insert(v.end(), 7);
        CHECK(v.front() == 7);
        CHECK(v.back() == 7);
    }

    SECTION("middle") {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
            v.push_back(i);
        auto iter = v.begin();
        ++iter;
        v.insert(iter, 41);
        CHECK(*iter == 41);
        int data[] = {0, 41, 1, 2, 3, 4};
        CHECK(v.size() == 6);
        for (int i = 0; i < 6; ++i)
            CHECK(v[i] == data[i]);
    }
}

TEST_CASE("erase") {
    Vector<int> v;
    for (int i = 0; i < 5; ++i)
        v.push_back(i);

    SECTION("front") {
        auto iter = v.erase(v.begin());
        CHECK(*iter == 1);
        CHECK(v.size() == 4);
        CHECK(v.front() == 1);
    }

    SECTION("back") {
        auto iter = v.erase(v.end());
        CHECK(iter == v.end());
        CHECK(v.size() == 5);
    }

    SECTION("middle") {
        auto iter = v.begin();
        ++iter;
        iter = v.erase(iter);
        CHECK(*iter == 2);
        CHECK(v.size() == 4);
    }
}

TEST_CASE("swap") {
    SECTION("swap two vectors") {
        Vector<int> v1, v2;
        for (int i = 0; i < 5; ++i)
            v1.push_back(1);
        for (int j = 0; j < 3; ++j)
            v2.push_back(2);
        v1.swap(v2);
        CHECK(v1.size() == 3);
        for (int i = 0; i < 3; ++i)
            CHECK(v1[i] == 2);
        CHECK(v2.size() == 5);
        for (int j = 0; j < 5; ++j)
            CHECK(v2[j] == 1);
    }
}
