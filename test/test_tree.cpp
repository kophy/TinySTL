#include <cstdlib>
#include "tree.hpp"
#include "utils.hpp"

#include <catch.hpp>

using namespace TinySTL;

static bool ComparePair(const Pair<int, int> &a, const Pair<int, int> &b) {
    return a.first < b.first;
}

TEST_CASE("capacity") {
    SECTION("empty tree") {
        Tree<int> t;
        CHECK(t.empty());
    }

    SECTION("not empty tree") {
        Tree<int> t;
        for (int i = 0; i < 5; ++i)
            t.insert(i);
        CHECK(t.size() == 5);
    }
}

TEST_CASE("insert and erase") {
    SECTION("tree of int") {
        Tree<int> t;
        for (int i = 0; i < 5; ++i)
            t.insert(i);
        for (int i = 0; i < 5; ++i)
            CHECK(t.count(i) == 1);
        CHECK(t.count(6) == 0);
        t.erase(3);
        CHECK(t.size() == 4);
        CHECK(t.count(3) == 0);
    }

    SECTION("tree of pair") {
        Tree<Pair<int, int>> t(ComparePair);
        for (int i = 0; i < 10; ++i)
            t.insert(MakePair(i / 2, i));
        CHECK(t.size() == 5);
        for (int i = 0; i < 5; ++i)
            CHECK(t.count(MakePair(i, 0)) == 1);
        t.erase(MakePair(3, 0));
        CHECK(t.count(MakePair(3, 0)) == 0);
    }
}

TEST_CASE("clear") {
    SECTION("insert, clear and insert") {
        Tree<int> t;
        for (int i = 0; i < 5; ++i)
            t.insert(i);
        t.clear();
        CHECK(t.empty());
        for (int i = 0; i < 5; ++i)
            t.insert(i);
        CHECK(t.size() == 5);
    }
}
