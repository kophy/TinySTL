#ifndef __TINYSTL_PRIORITY_QUEUE__
#define __TINYSTL_PRIORITY_QUEUE__

#include <stdexcept>

#include "vector.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename T, typename Container = Vector<T>>
    class PriorityQueue {
        public:
            // access top element
            T &top() { return data.front(); }

            // checks whether the heap is empty
            bool empty() { return data.empty(); }

            // returns the number of elements
            unsigned int size() { return data.size(); }

            // insert element
            void push(const T &val) {
                data.push_back(val);
                siftUp(data.size() - 1);
            }

            // remove top element
            void pop() {
                Swap(data.front(), data.back());
                data.pop_back();
                siftDown(0);
            }

            // constructor
            PriorityQueue(bool (*_cmp)(const T &a, const T &b) = Less<T>) : cmp(_cmp) {}

        private:
            // fix lower level
            void siftDown(unsigned int pos) {
                unsigned int left = pos * 2 + 1, right = pos * 2 + 2;
                if (left >= data.size()) {
                    return;
                } else if (right == data.size()) {
                    if (!cmp(data[pos], data[left]))
                        Swap(data[pos], data[left]);
                } else {
                    if (cmp(data[pos], data[left]) && cmp(data[pos], data[right]))
                        return;
                    unsigned int pivot = cmp(data[left], data[right])? left : right;
                    Swap(data[pos], data[pivot]);
                    siftDown(pivot);
                }
            }

            // fix upper level
            void siftUp(unsigned int pos) {
                unsigned int parent = (pos - 1) / 2;
                if (pos == 0 || cmp(data[parent], data[pos]))
                    return;
                Swap(data[parent], data[pos]);
                siftUp(parent);
            }

            Container data;
            bool (*cmp)(const T &a, const T &b);
    };
};

#endif
