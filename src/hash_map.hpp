#ifndef __TINYSTL_HASH_MAP__
#define __TINYSTL_HASH_MAP__

#include "hash_table.hpp"
#include "allocator.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename Key, typename Value>
    static bool isEqualKey(const Pair<const Key, Value> &a, const Pair<const Key, Value> &b) {
        return a.first == b.first;
    }

    template <typename Key, typename Value>
    static unsigned long hashByKey(const Pair<const Key, Value> &a) {
        return Hash<Key>(a.first);
    }

    template <typename Key, typename Value, class Alloc = Allocator<Pair<const Key, Value>>>
    class HashMap : public HashTable<Pair<const Key, Value>, Alloc> {
        public:

            class Iterator : public ForwardIterator {
                public:
                    bool operator ==(const Iterator &I) {
                        return (this->bucket_id == I.bucket_id && this->pos == I.pos);
                    }

                    bool operator !=(const Iterator &I) {
                        return (this->bucket_id != I.bucket_id || this->pos != I.pos);
                    }

                    Pair<const Key, Value> &operator *() {
                        return *pos;
                    }

                    Pair<const Key, Value> *operator ->() {
                        return &(*pos);
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

                    Iterator(Vector<List<Pair<const Key, Value>>> *_data = nullptr) {
                        data = _data;
                        bucket_id = 0;
                    }

                private:
                    Vector<List<Pair<const Key, Value>>> *data;
                    unsigned int bucket_id;
                    typename List<Pair<const Key, Value>>::Iterator pos;

                    void advance() {
                        ++pos;
                        while (pos == (*data)[bucket_id].end()) {
                            ++bucket_id;
                            if (bucket_id == (*data).size())
                                break;
                            pos = (*data)[bucket_id].begin();
                        }
                    }

                friend class HashMap<Key, Value>;
            };

            // iterator to the beginning
            Iterator begin() {
                Iterator temp(HashTable<Pair<const Key, Value>>::data);
                if (this->empty()) {
                    temp.bucket_id = HashTable<Pair<const Key, Value>>::bucket_number - 1;
                    temp.pos = (*HashTable<Pair<const Key, Value>>::data).back().end();
                } else {
                    int id = 0;
                    while ((*HashTable<Pair<const Key, Value>>::data)[id].empty())
                        ++id;
                    temp.bucket_id = id;
                    temp.pos = (*HashTable<Pair<const Key, Value>>::data)[id].begin();
                }
                return temp;
            }

            // iterator to the end
            Iterator end() {
                Iterator temp(HashTable<Pair<const Key, Value>>::data);
                temp.bucket_id = HashTable<Pair<const Key, Value>>::bucket_number;
                temp.pos = (*HashTable<Pair<const Key, Value>>::data).back().end();
                return temp;
            }

            // iterator to element with specific key
            Iterator find(const Key &k) {
                auto kv = MakePair<const Key, Value>(k, Value());
                unsigned int id = this->hash(kv) % HashTable<Pair<const Key, Value>>::bucket_number;
                Iterator temp;
                temp.bucket_id = id;
                for (auto iter = (*HashTable<Pair<const Key, Value>>::data)[id].begin();
                         iter != (*HashTable<Pair<const Key, Value>>::data)[id].end(); ++iter) {
                    if (HashTable<Pair<const Key, Value>>::pred(*iter, kv)) {
                        temp.pos = iter;
                        return temp;
                    }
                }
                return this->end();
            }

            // access element
            Value &operator [](const Key &k) {
                auto iter = find(k);
                if (iter == this->end()) {
                    insert(k, Value());
                    iter = find(k);
                }
                return iter->second;
            }

            // insert wrapper
            void insert(const Key &k, const Value &v) {
                HashTable<Pair<const Key, Value>>::insert(MakePair<const Key, Value>(k, v));
            }

            // erase wrapper
            void erase(const Key &k) {
                HashTable<Pair<const Key, Value>>::erase(MakePair<const Key, Value>(k, Value()));
            }

            // count wrapper
            unsigned int count(const Key &k) {
                return HashTable<Pair<const Key, Value>>::count(MakePair<const Key, Value>(k, Value()));
            }

            HashMap(bool (*_pred)(const Pair<const Key, Value> &a, const Pair<const Key, Value> &b) = isEqualKey<Key, Value>,
                    unsigned long (*_hash)(const Pair<const Key, Value> &val) = hashByKey<Key, Value>,
                    double _alpha = 1.0) :
                    HashTable<Pair<const Key, Value>, Alloc>::HashTable(_pred, _hash, _alpha) {}

        friend class Iterator;
    };
};

#endif
