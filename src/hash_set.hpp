#ifndef __TINYSTL_HASH_SET__
#define __TINYSTL_HASH_SET__

#include "hash_table.hpp"
#include "allocator.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename T, class Alloc = Allocator<list_node<T>>>
    class HashSet : public HashTable<T, Alloc> {
        public:
            class Iterator : public ForwardIterator {
                public:
                    bool operator ==(const Iterator &I) {
                        return (this->bucket_id == I.bucket_id && this->pos == I.pos);
                    }

                    bool operator !=(const Iterator &I) {
                        return (this->bucket_id != I.bucket_id || this->pos != I.pos);
                    }

                    const T &operator *() {
                        return *pos;
                    }

                    Iterator operator ++() {
                        advance();
                        return *this;
                    }

                    Iterator operator ++(int dummy) {
                        auto temp = *this;
                        advance();
                        return temp;
                    }

                    Iterator(Vector<List<T>> *_data = nullptr) {
                        data = _data;
                        bucket_id = 0;
                    }

                private:
                    Vector<List<T>> *data;
                    unsigned int bucket_id;
                    typename List<T>::Iterator pos;

                    void advance() {
                        ++pos;
                        while (pos == (*data)[bucket_id].end()) {
                            ++bucket_id;
                            if (bucket_id == (*data).size())
                                break;
                            pos = (*data)[bucket_id].begin();
                        }
                    }

                friend class HashSet<T>;
            };

            // iterator to the beginning
            Iterator begin() {
                Iterator temp(HashTable<T>::data);
                if (this->empty()) {
                    temp.bucket_id = HashTable<T>::bucket_number - 1;
                    temp.pos = (*HashTable<T>::data).back().end();
                } else {
                    int id = 0;
                    while ((*HashTable<T>::data)[id].empty())
                        ++id;
                    temp.bucket_id = id;
                    temp.pos = (*HashTable<T>::data)[id].begin();
                }
                return temp;
            }

            // iterator to the end
            Iterator end() {
                Iterator temp(HashTable<T>::data);
                temp.bucket_id = HashTable<T>::bucket_number;
                temp.pos = (*HashTable<T>::data).back().end();
                return temp;
            }

            // iterator to element with specific key
            Iterator find(const T &val) {
                unsigned int id = this->hash(val) % HashTable<T>::bucket_number;
                Iterator temp;
                temp.bucket_id = id;
                for (auto iter = (*HashTable<T>::data)[id].begin(); iter != (*HashTable<T>::data)[id].end(); ++iter) {
                    if (HashTable<T>::pred(*iter, val)) {
                        temp.pos = iter;
                        return temp;
                    }
                }
                return this->end();
            }

            // constructor
            HashSet(bool (*_pred)(const T &a, const T &b) = Equal<T>,
                    unsigned long (*_hash)(const T &val) = Hash<T>,
                    double _alpha = 1.0) :
                    HashTable<T>::HashTable(_pred, _hash, _alpha) {}

        friend class Iterator;
    };
};

#endif
