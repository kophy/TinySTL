#ifndef __TINYSTL_VECTOR__
#define __TINYSTL_VECTOR__

#include <stdexcept>
#include "allocator.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename T, class Alloc = Allocator<T>>
    class Vector {
        public:
            /*** 1. Element Access ***/

            // access specified element
            T &operator [](int pos) {
                if (pos < 0 || pos >= used)
                    throw std::out_of_range("index out of range");
                return data[pos];
            }

            // access first element
            T &front() {
                if (this->empty())
                    throw std::out_of_range("index out of range");
                return data[0];
            }

            // access last element
            T &back() {
                if (this->empty())
                    throw std::out_of_range("index out of range");
                return data[used - 1];
            }

            /*** 2. Iterator ***/
            class Iterator : public ForwardIterator {
                public:
                    bool operator ==(const Iterator &I) { return (this->curr == I.curr); }
                    bool operator !=(const Iterator &I) { return (this->curr != I.curr); }

                    T &operator *() { return *curr; }

                    Iterator operator ++() {
                        ++curr;
                        return *this;
                    }

                    Iterator operator ++(int dummy) {
                        auto temp = *this;
                        ++curr;
                        return temp;
                    }

                    Iterator(T *_curr = nullptr) : curr(_curr) {}

                private:
                    T *curr;

                friend class Vector<T>;
            };

            class ReverseIterator : public BackwardIterator {
                public:
                    bool operator ==(const ReverseIterator &I) { return (this->curr == I.curr); }
                    bool operator !=(const ReverseIterator &I) { return (this->curr != I.curr); }

                    T &operator *() { return *curr; }

                    ReverseIterator operator ++() {
                        --curr;
                        return *this;
                    }

                    ReverseIterator operator ++(int dummy) {
                        auto temp = *this;
                        --curr;
                        return temp;
                    }

                    ReverseIterator(T *_curr = nullptr) : curr(_curr) {}

                private:
                    T *curr;

                friend class Vector<T>;
            };

            // iterator to the beginning
            Iterator begin() { return Iterator(this->empty()? nullptr : &this->front()); }

            // iterator to the end
            Iterator end() { return Iterator(this->empty()? nullptr : &(this->back()) + 1); }

            // reverse iterator to the beginning
            ReverseIterator rbegin() { return ReverseIterator(this->empty()? nullptr : &this->back()); }

            // reverse iterator to the end
            ReverseIterator rend() { return ReverseIterator(this->empty()? nullptr : &(this->front()) - 1); }

            /*** 3. Capacity ***/

            // checks whether the vector is empty
            bool empty() { return (used == 0); }

            // returns the number of elements
            unsigned int size() { return used; }

            // change size to element number
            void resize() { this->resize(used); }

            // change size to given value
            void resize(unsigned int new_capacity) {
                T *temp = alloc.allocate(new_capacity);
                unsigned int new_used = Min(used, new_capacity);
                alloc.construct(temp, new_used);
                for (int i = 0; i < new_used; ++i)
                    temp[i] = data[i];
                if (data != nullptr) {
                    alloc.destroy(data, used);
                    alloc.deallocate(data);
                }
                data = temp;
                used = new_used;
                capacity = new_capacity;
            }

            /*** Modifiers ***/

            // add element to the end
            void push_back(const T &val) {
                if (used >= capacity)
                    this->resize(Max(1u, 2 * capacity));
                alloc.construct(data + used, 1);
                data[used] = val;
                ++used;
            }

            // delete last element
            void pop_back() {
                --used;
                alloc.destroy(data + used, 1);
            }

            // insert elements
            Iterator insert(Iterator pos, const T &val) {
                if (this->empty()) {
                    push_back(val);
                    return this->begin();
                } else {
                    if (used >= capacity)
                        this->resize(Max(1u, 2 * capacity));
                    unsigned int pivot = pos.curr - data;
                    for (int i = used; i > pivot; --i)
                        data[i] = data[i - 1];
                    alloc.construct(data + pivot, 1);
                    data[pivot] = val;
                    ++used;
                    return Iterator(data + pivot);
                }
            }

            // erase elements
            Iterator erase(Iterator pos) {
                if (this->empty() || pos == this->end()) {
                    return pos;
                } else {
                    unsigned int pivot = pos.curr - data;
                    alloc.destroy(data + pivot, 1);
                    for (int i = pivot; i < used; ++i)
                        data[i] = data[i + 1];
                    --used;
                    return Iterator(data + pivot);
                }
            }

            // swap content with another vector
            void swap(Vector<T> &other) {
                Swap(this->data, other.data);
                Swap(this->used, other.used);
                Swap(this->capacity, other.capacity);
            }

            // clear content
            void clear() {
                alloc.destroy(data, used);
                used = 0;
            }

            /*** Constructor and Destructor ***/

            // constructor
            Vector(unsigned int _size = 0) : data(nullptr), used(0), capacity(0) {
                if (_size > 0) {
                    data = alloc.allocate(_size);
                    alloc.construct(data, _size);
                    used = _size;
                    capacity = _size;
                }
            }

            // destructor
            ~Vector() {
                clear();
                alloc.deallocate(data);
            }

        private:
            T *data;
            unsigned int used, capacity;
            Alloc alloc;

        friend class Iterator;
        friend class ReverseIterator;
    };
};

#endif
