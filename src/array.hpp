#ifndef __TINYSTL_ARRAY__
#define __TINYSTL_ARRAY__

#include <stdexcept>
#include "utils.hpp"

namespace TinySTL {
    template <typename T, unsigned int N>
    class Array {
        public:
            /*** 1. Element Access ***/

            // access specified elements with bounds checking
            T &at(int pos) {
                if (pos < 0 || pos >= N)
                    throw std::out_of_range("index out of range");
                return data[pos];
            }

            // access specified elements
            T &operator [](int pos) {
                return data[pos];
            }

            // access first element
            T &front() {
                if (this->empty())
                    throw std::out_of_range("empty array");
                return data[0];
            }

            // access last element
            T &back() {
                if (this->empty())
                    throw std::out_of_range("empty array");
                return data[N - 1];
            }

            /*** 2. Iterator ***/

            class Iterator : public ForwardIterator {
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
                        return Iterator(++curr);
                    }

                    Iterator operator ++(int dummy) {
                        return Iterator(curr++);
                    }

                    Iterator(T *_curr = nullptr) : curr(_curr) {}

                private:
                    T *curr;

                friend class Array<T, N>;
            };

            class ReverseIterator : public BackwardIterator {
                public:
                    bool operator ==(const ReverseIterator &I) {
                        return (this->curr == I.curr);
                    }

                    bool operator !=(const ReverseIterator &I) {
                        return (this->curr != I.curr);
                    }

                    T &operator *() {
                        return *curr;
                    }

                    ReverseIterator operator ++() {
                        return ReverseIterator(--curr);
                    }

                    ReverseIterator operator ++(int dummy) {
                        return ReverseIterator(curr--);
                    }

                    ReverseIterator(T *_curr = nullptr) : curr(_curr) {}

                private:
                    T *curr;

                friend class Array<T, N>;
            };

            // iterator to the beginning
            Iterator begin() {
                return Iterator(this->empty()? nullptr : &this->front());
            }

            // iterator to the end
            Iterator end() {
                return Iterator(this->empty()? nullptr : &(this->back()) + 1);
            }

            // reverse iterator to the beginning
            ReverseIterator rbegin() {
                return ReverseIterator(this->empty()? nullptr : &this->back());
            }

            // reverse iterator to the end
            ReverseIterator rend() {
                return ReverseIterator(this->empty()? nullptr : &(this->front()) - 1);
            }

            /*** 3. Capacity ***/

            // checks whether the array is empty
            bool empty() {
                return (N == 0);
            }

            // returns the number of elements
            unsigned int size() {
                return N;
            }

            /*** 4. Operations ***/

            // fill the array with given value
            void fill(const T &val) {
                for (int i = 0; i < N; ++i)
                    this->data[i] = val;
            }

            // swap content with another array
            void swap(Array<T, N> &other) {
                for (int i = 0; i < N; ++i)
                    Swap(this->data[i], other.data[i]);
            }

            /*** 5. Constructor and Destructor ***/

            // constructor
            Array() {
                data = new T[N];
            }

            // destructor
            ~Array() {
                delete data;
            }

        private:
            T *data;

        friend class Iterator;
        friend class ReverseIterator;
    };
};

#endif
