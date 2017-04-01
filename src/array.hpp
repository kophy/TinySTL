#ifndef __TINYSTL_ARRAY__
#define __TINYSTL_ARRAY__

#include <stdexcept>

namespace TinySTL {
    template <typename T, unsigned int N>
    class Array {
        public:
            /*** 1. Element Access ***/

            // access specified elements with bounds checking
            T &at(int idx) {
                if (idx < 0 || idx >= N)
                    throw std::out_of_range("index out of range");
                return data[idx];
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

            template <typename U, unsigned int M>
            class Iterator {
                public:
                    bool operator ==(const Iterator<U, M> &I) {
                        return (this->curr == I.curr);
                    }

                    bool operator !=(const Iterator<U, M> &I) {
                        return (this->curr != I.curr);
                    }

                    U& operator *() {
                        return *curr;
                    }

                    Iterator<U, M> operator ++() {
                        advance();
                        return Iterator<U, M>(this->curr);
                    }

                    Iterator<U, M> operator ++(int dummy) {
                        Iterator<U, M> temp(this->curr);
                        advance();
                        return temp;
                    }

                    Iterator(U *_curr = nullptr) : curr(_curr) {}

                private:
                    void advance() {
                        ++this->curr;
                    }

                    U *curr;
            };

            // iterator to the beginning
            Iterator<T, N> begin() {
                return Iterator<T, N>(this->empty()? nullptr : &this->front());
            }

            // iterator to the end
            Iterator<T, N> end() {
                return Iterator<T, N>(this->empty()? nullptr : &this->back());
            }

            /*** 3. Capacity ***/

            // checks whether the container is empty
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
                for (int i = 0; i < N; ++i) {
                    auto temp = this->data[i];
                    this->data[i] = other.data[i];
                    other.data[i] = temp;
                }
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
    };
};

#endif
