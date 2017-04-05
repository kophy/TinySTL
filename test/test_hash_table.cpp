#include <cstdlib>
#include "hash_table.hpp"

#include "catch.hpp"

using TinySTL::HashTable;

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

TEST_CASE("insert and erase") {
    SECTION("hash table of int") {
        HashTable<int> ht;
        CHECK(ht.count(7) == 0);
        ht.insert(7);
        CHECK(ht.count(7) == 1);
        ht.insert(7);
        CHECK(ht.count(7) == 1);
        ht.erase(7);
        CHECK(ht.count(7) == 0);
    }
}
