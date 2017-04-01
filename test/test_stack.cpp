#include <cstdlib>
#include "stack.hpp"

#include "catch.hpp"

using TinySTL::Stack;

TEST_CASE("everything together") {
    SECTION("empty and size") {
        Stack<int> stk;
        CHECK(stk.empty());
        for (int i = 0; i < 5; ++i)
            stk.push(i);
        CHECK(stk.size() == 5);
    }

    SECTION("top, push and pop") {
        Stack<int> stk;
        for (int i = 0; i < 5; ++i)
            stk.push(i);
        CHECK(stk.top() == 4);
        stk.pop();
        CHECK(stk.top() == 3);
    }

    SECTION("swap") {
        Stack<int> stk1, stk2;
        for (int i = 0; i < 3; ++i)
            stk1.push(1);
        for (int j = 0; j < 5; ++j)
            stk2.push(2);
        stk1.swap(stk2);
        CHECK(stk1.size() == 5);
        CHECK(stk1.top() == 2);
        CHECK(stk2.size() == 3);
        CHECK(stk2.top() == 1);
    }
}
