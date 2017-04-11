#ifndef __TINYSTL_STACK__
#define __TINYSTL_STACK__

#include "list.hpp"

namespace TinySTL {
    template <typename T, class Container = List<T>>
    class Stack {
        public:
            /*** 1. Element Access ***/

            // access next element
            T& top() { return data.back(); }

            /*** 2. Capacity ***/

            // checks whether the stack is empty
            bool empty() { return data.empty(); }

            // returns the number of elements
            unsigned int size() { return data.size(); }

            /*** 3. Modifiers ***/

            // insert element
            void push(const T& val) { data.push_back(val); }

            // remove top element
            void pop() { data.pop_back(); }

            // swap content
            void swap(Stack<T> &other) { this->data.swap(other.data); }

        private:
            Container data;
    };
};

#endif
