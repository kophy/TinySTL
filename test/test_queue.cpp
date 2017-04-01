#include <cstdlib>
#include "queue.hpp"

#include "catch.hpp"

using TinySTL::Queue;

TEST_CASE("everything together") {
    SECTION("empty and size") {
        Queue<int> que;
        CHECK(que.empty());
        for (int i = 0; i < 5; ++i)
            que.push(i);
        CHECK(que.size() == 5);
    }

    SECTION("front and back, push and pop") {
        Queue<int> que;
        for (int i = 0; i < 5; ++i)
            que.push(i);
        CHECK(que.front() == 0);
        CHECK(que.back() == 4);
        que.pop();
        CHECK(que.front() == 1);
    }

    SECTION("swap") {
        Queue<int> que1, que2;
        for (int i = 0; i < 3; ++i)
            que1.push(1);
        for (int j = 0; j < 5; ++j)
            que2.push(2);
        que1.swap(que2);
        CHECK(que1.size() == 5);
        CHECK(que1.front() == 2);
        CHECK(que2.size() == 3);
        CHECK(que2.front() == 1);
    }
}
