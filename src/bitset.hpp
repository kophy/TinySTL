#ifndef __TINYSTL_BITSET__
#define __TINYSTL_BITSET__

#include <stdexcept>
#include <cmath>

using std::ceil;

namespace TinySTL {
    template <unsigned int N>
    class Bitset {
        public:
            /*** 1. Bit Access ***/

            // count bits set
            unsigned int count() {
                int cnt = 0;
                for (int i = 0; i < N; ++i)
                    if (test(i))
                        ++cnt;
                return cnt;
            }

            // return size
            unsigned int size() { return N; }

            // return bit value
            bool test(unsigned int pos) {
                if (pos >= N)
                    throw std::out_of_range("index out of range");
                int i = pos / sizeof(char), j = pos % sizeof(char);
                return (data[i] & (1u << j)) != 0;
            }

            // test if any bit is set
            bool any() {
                for (int i = 0; i < N; ++i)
                    if (test(i))
                        return true;
                return false;
            }

            // test if no bit is set
            bool none() {
                for (int i = 0; i < N; ++i)
                    if (test(i))
                        return false;
                return true;
            }

            // test if all bits are set
            bool all() {
                for (int i = 0; i < N; ++i)
                    if (!test(i))
                        return false;
                return true;
            }

            class reference {
                public:
                    void operator =(bool val) { data->set(pos, val); }
                    void operator =(const reference &r) { data->set(pos, data->test(r.pos)); }

                    // implicit type conversion
                    operator bool() const { return data->test(pos); }

                    reference(Bitset<N> *_data, unsigned int _pos) : data(_data), pos(_pos) {}
                private:
                    Bitset<N> *data;
                    unsigned int pos;

                friend class Bitset<N>;
            };

            // access bit: read
            reference operator [](unsigned int pos) { return reference(this, pos); }

            /*** 2. Bit Operations ***/

            // set bits
            void set(unsigned int pos, bool val = true) {
                if (pos >= N)
                    throw std::out_of_range("index out of range");
                if (!val)
                    reset(pos);
                else {
                    int i = pos / sizeof(char), j = pos % sizeof(char);
                    data[i] = data[i] | (1u << j);
                }
            }

            // reset bits
            void reset(unsigned int pos) {
                if (pos >= N)
                    throw std::out_of_range("index out of range");
                int i = pos / sizeof(char), j = pos % sizeof(char);
                data[i] = data[i] & (~(1u << j));
            }

            /*** 3. Bitset Operations ***/

            // convert to unsigned long integer
            unsigned long to_ulong() {
                unsigned long result = 0;
                int temp = 1;
                for (int i = 0; i < N; ++i) {
                    if (test(i))
                        result += temp;
                    temp <<= 1;
                }
                return result;
            }

            /*** 4. Constructor and Destructor ***/

            // constructor
            Bitset(unsigned long val = 0) {
                unsigned int len = ceil(N * 1.0 / sizeof(char));
                data = new char[len];
                for (int i = 0; i < N; ++i) {
                    set(i, val % 2 == 1);
                    val /= 2;
                }
            }

            // destructor
            ~Bitset() { delete data; }

        private:
            char *data;

        friend class reference;
    };
};

#endif
