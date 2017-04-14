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
                    bool operator ==(const Iterator &I) { return (this->data == I.data && this->e == I.e); }
                    bool operator !=(const Iterator &I) { return (this->data != I.data || this->e != I.e); }

                    Pair<const Key, Value> &operator *()  { return *(e.second); }
                    Pair<const Key, Value> *operator ->() { return &(*(e.second)); }

                    Iterator operator ++() {
                        advance();
                        return *this;
                    }

                    Iterator operator ++(int dummy) {
                        auto temp = *this;
                        advance();
                        return temp;
                    }

                    Iterator(HashMap<Key, Value, Alloc> *_data, typename HashMap<Key, Value>::HashEntry _e) :
                        data(_data), e(_e) {}

                private:
                    HashMap<Key, Value, Alloc> *data;
                    typename HashMap<Key, Value>::HashEntry e;

                    void advance() { e = data->findNext(e); }

                friend class HashMap<Key, Value>;
            };

            // iterator to the beginning
            Iterator begin() { return Iterator(this, base::findBegin()); }

            // iterator to the end
            Iterator end()   { return Iterator(this, base::findEnd()); }

            // iterator to element with specific key
            Iterator find(const Key &k) {
                auto kv = MakePair<const Key, Value>(k, Value());
                return Iterator(this, base::find(kv));
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
            void insert(const Key &k, const Value &v) { base::insert(MakePair<const Key, Value>(k, v)); }

            // erase wrapper
            void erase(const Key &k) { base::erase(MakePair<const Key, Value>(k, Value())); }

            // count wrapper
            unsigned int count(const Key &k) { return base::count(MakePair<const Key, Value>(k, Value())); }

            HashMap(bool (*_pred)(const Pair<const Key, Value> &a, const Pair<const Key, Value> &b) = isEqualKey<Key, Value>,
                    unsigned long (*_hash)(const Pair<const Key, Value> &val) = hashByKey<Key, Value>, double _alpha = 1.0) :
                    HashTable<Pair<const Key, Value>, Alloc>::HashTable(_pred, _hash, _alpha) {}

        private:
            typedef HashTable<Pair<const Key, Value>> base;

        friend class Iterator;
    };
};

#endif
