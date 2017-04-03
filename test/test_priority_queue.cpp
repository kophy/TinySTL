#include <cstdlib>
#include "priority_queue.hpp"
#include "utils.hpp"

#include <catch.hpp>

using TinySTL::PriorityQueue;
using TinySTL::Greater;

TEST_CASE("everything together") {
    SECTION("empty and size") {
        PriorityQueue<int> pq;
        CHECK(pq.empty());
        for (int i = 0; i < 5; ++i)
            pq.push(i);
        CHECK(pq.size() == 5);
    }

    SECTION("top, push and pop: default compare function") {
        PriorityQueue<int> pq;
        int data[] = {3, 1, 0, 4, 2};
        for (int i = 0; i < 5; ++i)
            pq.push(data[i]);
        int i = 0;
        while (!pq.empty()) {
            CHECK(pq.top() == i++);
            pq.pop();
        }
        CHECK(i == 5);
    }

    SECTION("top, push and pop: user defined function") {
        PriorityQueue<int> pq(Greater<int>);
        int data[] = {3, 1, 0, 4, 2};
        for (int i = 0; i < 5; ++i)
            pq.push(data[i]);
        int i = 5;
        while (!pq.empty()) {
            CHECK(pq.top() == --i);
            pq.pop();
        }
        CHECK(i == 0);
    }
}
