#ifndef __TINYSTL_QUEUE__
#define __TINYSTL_QUEUE__

#include "list.hpp"

namespace TinySTL {
    template <typename T, class Container = List<T>>
    class Queue {
        public:
            /*** 1. Element Access ***/

            // access next element
            T& front() { return data.front(); }

            // access last element
            T& back()  { return data.back(); }

            /*** 2. Capacity ***/

            // checks whether the queue is empty
            bool empty() { return data.empty(); }

            // returns the number of elements
            unsigned int size() { return data.size(); }

            /*** 3. Modifiers ***/

            // insert element
            void push(const T &val) { data.push_back(val); }

            // remove next element
            void pop() { data.pop_front(); }

            void swap(Queue<T> &other) { this->data.swap(other.data); }

        private:
            Container data;
    };
};

#endif
