#ifndef __TINYSTL_HASH_SET__
#define __TINYSTL_HASH_SET__

#include "hash_table.hpp"
#include "allocator.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename T, class Alloc = Allocator<T>>
    class HashSet : public HashTable<T, Alloc> {
        public:
            class Iterator : public ForwardIterator {
                public:
                    bool operator ==(const Iterator &I) { return (this->data == I.data && this->e == I.e); }
                    bool operator !=(const Iterator &I) { return (this->data != I.data || this->e != I.e); }

                    const T &operator *() { return *(e.second); }

                    Iterator operator ++() {
                        advance();
                        return *this;
                    }

                    Iterator operator ++(int dummy) {
                        auto temp = *this;
                        advance();
                        return temp;
                    }

                    Iterator(HashSet<T> *_data, typename HashSet<T>::HashEntry _e) : data(_data), e(_e) {}

                private:
                    HashSet<T> *data;
                    typename HashSet<T>::HashEntry e;

                    void advance() { e = data->findNext(e); }

                friend class HashSet<T>;
            };

            // iterator to the beginning
            Iterator begin() { return Iterator(this, base::findBegin()); }

            // iterator to the end
            Iterator end()   { return Iterator(this, base::findEnd()); }

            // iterator to element with specific key
            Iterator find(const T &val) { return Iterator(this, base::find(val)); }

            // constructor
            HashSet(bool (*_pred)(const T &a, const T &b) = Equal<T>, unsigned long (*_hash)(const T &val) = Hash<T>,
                    double _alpha = 1.0) : HashTable<T, Alloc>::HashTable(_pred, _hash, _alpha) {}

        private:
            typedef HashTable<T> base;

        friend class Iterator;
    };
};

#endif
