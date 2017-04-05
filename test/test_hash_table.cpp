#include <cstdlib>
#include "hash_table.hpp"

#include "catch.hpp"

using namespace TinySTL;

static bool ComparePair(const Pair<int, int> &a, const Pair<int, int> &b) {
    return a.first == b.first;
}

unsigned long HashPair(const Pair<int, int> &a) {
    return Hash(a.first);
}

TEST_CASE("capacity") {
    SECTION("empty table") {
        HashTable<int> ht;
        CHECK(ht.empty());
        CHECK(ht.size() == 0);
    }

    SECTION("not empty table") {
        HashTable<int> ht;
        for (int i = 0; i < 5; ++i)
            ht.insert(i);
        CHECK(!ht.empty());
        CHECK(ht.size() == 5);
    }
}

TEST_CASE("Vector and List") {
    SECTION("dummy") {
        auto pv = new Vector<Vector<int>>(10);
        CHECK((*pv)[0].empty());
        delete pv;
    }
}

TEST_CASE("insert and erase") {
    SECTION("hash table of int") {
        HashTable<int> ht;
        for (int i = 0; i < 5; ++i)
            ht.insert(i);
        for (int i = 0; i < 5; ++i)
            CHECK(ht.count(i) == 1);
        CHECK(ht.count(7) == 0);
        ht.erase(3);
        CHECK(ht.count(3) == 0);
    }

    SECTION("hash table of pair") {
        HashTable<Pair<int, int>> ht(ComparePair, HashPair);
        for (int i = 0; i < 10; ++i)
            ht.insert(MakePair(i / 2, i));
        CHECK(ht.size() == 5);
    }
}

TEST_CASE("iterator") {
    SECTION("hash table of int") {
        HashTable<int> ht;
        Vector<int> data;
        for (int i = 0; i < 10; ++i) {
            ht.insert(i);
            data.push_back(i);
        }
        int i = 0;
        for (auto iter = ht.begin(); iter != ht.end(); ++iter) {
            CHECK(Count(data.begin(), data.end(), *iter) == 1);
            ++i;
        }
        CHECK(i == 10);
    }
}
