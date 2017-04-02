#ifndef __TINYSTL_ARRAY__
#define __TINYSTL_ARRAY__

#include <stdexcept>

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

            template <typename U>
            class Iterator {
                public:
                    bool operator ==(const Iterator<U> &I) {
                        return (this->curr == I.curr && this->forward == I.forward);
                    }

                    bool operator !=(const Iterator<U> &I) {
                        return (this->curr != I.curr || this->forward != I.forward);
                    }

                    U &operator *() {
                        return *curr;
                    }

                    Iterator<U> operator ++() {
                        advance();
                        return Iterator<U>(this->curr);
                    }

                    Iterator<U> operator ++(int dummy) {
                        Iterator<U> temp(this->curr);
                        advance();
                        return temp;
                    }

                    Iterator(U *_curr = nullptr, bool _forword = true) : curr(_curr), forward(_forword) {}

                private:
                    void advance() {
                        this->curr += (forward)? 1 : -1;
                    }

                    U *curr;
                    bool forward;
            };

            // iterator to the beginning
            Iterator<T> begin() {
                return Iterator<T>(this->empty()? nullptr : &this->front());
            }

            // iterator to the end
            Iterator<T> end() {
                return Iterator<T>(this->empty()? nullptr : &(this->back()) + 1);
            }

            // reverse iterator to the beginning
            Iterator<T> rbegin() {
                return Iterator<T>(this->empty()? nullptr : &this->back(), false);
            }

            // reverse iterator to the end
            Iterator<T> rend() {
                return Iterator<T>(this->empty()? nullptr : (&this->front()) - 1, false);
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
