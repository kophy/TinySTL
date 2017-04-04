#include <cstdlib>
#include <functional>
#include "utils.hpp"
#include "vector.hpp"
#include "list.hpp"

#include "catch.hpp"

using namespace TinySTL;

static bool ComparePairs(const Pair<int, int> &a, const Pair<int, int> &b) {
    return a.first == b.first;
}

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

TEST_CASE("Find and Count") {
    SECTION("Vector of int") {
        Vector<int> v(10);
        for (int i = 0; i < 10; ++i)
            v[i] = i / 2;
        CHECK(Find(v.begin(), v.end(), 2) != v.end());
        CHECK(Count(v.begin(), v.end(), 2) == 2);
    }

    SECTION("Vector of Pair") {
        Vector<Pair<int, int>> v(10);
        for (int i = 0; i < 10; ++i)
            v[i] = MakePair(i / 2, i);
        Pair<int, int> temp = MakePair(1, 1);
        CHECK(Find(v.begin(), v.end(), temp, ComparePairs) != v.end());
        CHECK(Count(v.begin(), v.end(), temp, ComparePairs) == 2);
    }

    SECTION("List of int") {
        List<int> l;
        for (int i = 0; i < 10; ++i)
            l.push_back(i / 2);
        CHECK(Find(l.begin(), l.end(), 2) != l.end());
        CHECK(Count(l.begin(), l.end(), 2) == 2);
    }

    SECTION("List of Pair") {
        List<Pair<int, int>> l;
        for (int i = 0; i < 10; ++i)
            l.push_back(MakePair(i / 2, i));
        Pair<int, int> temp = MakePair(1, 1);
        CHECK(Find(l.begin(), l.end(), temp, ComparePairs) != l.end());
        CHECK(Count(l.begin(), l.end(), temp, ComparePairs) == 2);
    }
}

TEST_CASE("Hash") {
    SECTION("int") {
        std::hash<int> h;
        CHECK(Hash(1) == h(1));
    }

    SECTION("string") {
        std::hash<std::string> h;
        std::string text = "Hello, TinySTL!";
        CHECK(Hash(text) == h(text));
    }
}
