#ifndef __TINYSTL_HASH_TABLE__
#define __TINYSTL_HASH_TABLE__

#include <iostream>
#include <cassert>
#include "vector.hpp"
#include "list.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename T>
    class HashTable {
        public:
            bool empty() {
                return (entry_number == 0);
            }

            unsigned int size() {
                return entry_number;
            }

            unsigned int count(const T &val) {
                unsigned int id = this->hash(val) % bucket_number;
                return Count((*data)[id].begin(), (*data)[id].end(), val, pred);
            }

            void insert(const T &val) {
                if (this->count(val) > 0)
                    return;
                unsigned int id = this->hash(val) % bucket_number;
                (*data)[id].push_back(val);
                ++entry_number;
            }

            void erase(const T &val) {
                if (this->count(val) == 0)
                    return;
                unsigned int id = this->hash(val) % bucket_number;
                auto iter = Find((*data)[id].begin(), (*data)[id].end(), val, pred);
                (*data)[id].erase(iter);
                --entry_number;
            }

            HashTable(double _alpha = 1.0,
                    unsigned long (*_hash)(const T &val) = Hash<T>,
                    bool (*_pred)(const T &a, const T &b) = Equal<T>){
                alpha = _alpha;
                hash = _hash;
                pred = _pred;

                data = new Vector<List<T>>(1);
                bucket_number = 1;
                entry_number = 0;
            }

        private:
            // technique used in redis
            Vector<List<T>> *data;
            unsigned int bucket_number, entry_number;
            double alpha;

            unsigned long (*hash)(const T &val);
            bool (*pred)(const T &a, const T &b);

            void rehash(unsigned int new_bucket_number) {}
    };
};

#endif
