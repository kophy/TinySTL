#ifndef __TINYSTL_VECTOR__
#define __TINYSTL_VECTOR__

#include <stdexcept>
#include "utils.hpp"

namespace TinySTL {
    template <typename T>
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
            class Iterator {
                public:
                    bool operator ==(const Iterator &I) {
                        return (this->curr == I.curr);
                    }

                    bool operator !=(const Iterator &I) {
                        return (this->curr != I.curr);
                    }

                    T &operator *() {
                        return *curr;
                    }

                    Iterator operator ++() {
                        advance();
                        return Iterator(this->curr);
                    }

                    Iterator operator ++(int dummy) {
                        Iterator temp(this->curr);
                        advance();
                        return temp;
                    }

                    Iterator(T *_curr = nullptr) : curr(_curr) {}

                private:
                    void advance() {
                        ++curr;
                    }

                    T *curr;

                friend class Vector<T>;
            };

            // iterator to the beginning
            Iterator begin() {
                return Iterator(this->empty()? nullptr : &this->front());
            }

            // iterator to the end
            Iterator end() {
                return Iterator(this->empty()? nullptr : &(this->back()) + 1);
            }

            /*** 3. Capacity ***/

            // checks whether the vector is empty
            bool empty() {
                return (used == 0);
            }

            // returns the number of elements
            unsigned int size() {
                return used;
            }

            // change size to element number
            void resize() {
                this->resize(used);
            }

            // change size to given value
            void resize(unsigned int new_capacity) {
                T *temp = new T[new_capacity];
                capacity = new_capacity;
                used = Min(used, new_capacity);
                for (int i = 0; i < used; ++i)
                    temp[i] = data[i];
                delete data;
                data = temp;
            }

            /*** Modifiers ***/

            // add element to the end
            void push_back(const T &val) {
                if (used >= capacity)
                    this->resize(Max(1u, 2 * capacity));
                data[used++] = val;
            }

            // delete last element
            void pop_back() {
                --used;
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
                    for (int i = pivot; i < used; ++i)
                        data[i] = data[i + 1];
                    --used;
                    return Iterator(data + pivot);
                }
            }

            // clear content
            void clear() {
                delete data;
                data = nullptr;
                used = 0;
                capacity = 0;
            }

            /*** Constructor and Destructor ***/

            // constructor
            Vector() : data(nullptr), used(0), capacity(0) {}

            // destructor
            ~Vector() {
                clear();
            }

        private:
            T *data;
            unsigned int used, capacity;

        friend Iterator;
    };
};

#endif
