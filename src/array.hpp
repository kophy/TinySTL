#ifndef __TINYSTL_ARRAY__
#define __TINYSTL_ARRAY__

#include <stdexcept>

namespace TinySTL {
    template <typename T, unsigned int N>
    class Array {
        public:

            // access specified elements with bounds checking
            T& at(int idx) {
                if (idx < 0 || idx >= N)
                    throw std::out_of_range("index out of range");
                return data[idx];
            }

            // access specified elements
            T& operator [](int pos) {
                return data[pos];
            }

            // checks whether the container is empty
            bool empty() {
                return (N == 0);
            }

            // returns the number of elements
            unsigned int size() {
                return N;
            }

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
