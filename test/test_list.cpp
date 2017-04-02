#include <cstdlib>
#include "list.hpp"

#include "catch.hpp"

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

TEST_CASE("pop back") {
    SECTION("empty list") {
        List<int> l;
        CHECK_THROWS_AS(l.pop_back(), std::out_of_range);
    }

    SECTION("not empty list") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(i);
        l.pop_back();
        CHECK(l.back() == 3);
    }
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

TEST_CASE("iterator") {
    SECTION("empty list") {
        List<int> l;
        CHECK(l.begin() == l.end());
    }

    SECTION("not empty list : traverse") {
        int data[] = {7, 11, 23, 41, 73};
        int cnt;
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(data[i]);
        cnt = 0;
        for (auto iter = l.begin(); iter != l.end(); ++iter)
            CHECK(*iter == data[cnt++]);
        CHECK(cnt == 5);
        cnt = 0;
        for (auto iter = l.begin(); iter != l.end(); iter++)
            CHECK(*iter == data[cnt++]);
        CHECK(cnt == 5);
    }

    SECTION("not empty list : edit") {
        int data[] = {7, 11, 23, 41, 73};
        int cnt;
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(data[i]);
        cnt = 0;
        for (auto iter = l.begin(); iter != l.end(); ++iter)
            *iter = 3 * data[cnt++];
        CHECK(cnt == 5);
        cnt = 0;
        for (auto iter = l.begin(); iter != l.end(); iter++)
            CHECK(*iter == 3 * data[cnt++]);
        CHECK(cnt == 5);
    }
}

TEST_CASE("insert") {
    SECTION("front") {
        List<int> l;
        l.insert(l.begin(), 17);
        CHECK(l.front() == 17);
        l.insert(l.begin(), 233);
        CHECK(l.front() == 233);
    }

    SECTION("back") {
        List<int> l;
        l.insert(l.end(), 17);
        CHECK(l.back() == 17);
        l.insert(l.end(), 233);
        CHECK(l.back() == 233);
    }

    SECTION("middle") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(i);
        auto iter = l.begin();
        iter++;
        l.insert(iter, 43);
        int data[] = {0, 43, 1, 2, 3, 4};
        int cnt = 0;
        for (iter = l.begin(); iter != l.end(); ++iter)
            CHECK(*iter == data[cnt++]);
        CHECK(cnt == 6);
    }
}

// TODO: add size check
TEST_CASE("erase") {
    SECTION("front") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(i);
        l.erase(l.begin());
        CHECK(l.front() == 1);
    }

    SECTION("back") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(i);
        l.erase(l.end());
        CHECK(l.back() == 4);
    }

    SECTION("middle") {
        List<int> l;
        for (int i = 0; i < 5; ++i)
            l.push_back(i);
        auto iter = l.begin();
        ++iter;
        iter = l.erase(iter);
        CHECK(*iter == 2);
        int data[] = {0, 2, 3, 4};
        int cnt = 0;
        for (iter = l.begin(); iter != l.end(); ++iter)
            CHECK(*iter == data[cnt++]);
        CHECK(cnt == 4);
    }
}

TEST_CASE("swap") {
    SECTION("swap two lists") {
        List<int> l1, l2;
        for (int i = 0; i < 3; ++i)
            l1.push_back(1);
        for (int j = 0; j < 5; ++j)
            l2.push_back(2);
        l1.swap(l2);
        CHECK(l1.size() == 5);
        CHECK(l2.size() == 3);
        auto iter1 = l1.begin(), iter2 = l2.end();
        while (iter1 != l1.end()) {
            CHECK(*iter1 == 2);
            ++iter1;
        }
        while (iter2 != l2.end()) {
            CHECK(*iter2 == 1);
            ++iter2;
        }
    }
}
