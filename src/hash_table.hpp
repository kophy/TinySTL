#ifndef __TINYSTL_HASH_TABLE__
#define __TINYSTL_HASH_TABLE__

#include <iostream>
#include "vector.hpp"
#include "list.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename T>
    class HashTable {
        public:
            // checks whether the hash table is empty
            bool empty() {
                return (entry_number == 0);
            }

            // returns the number of elements
            unsigned int size() {
                return entry_number;
            }

            // returns the number of elements matching specific key
            unsigned int count(const T &val) {
                unsigned int id = this->hash(val) % bucket_number;
                return Count((*data)[id].begin(), (*data)[id].end(), val, pred);
            }

            // inserts elements
            void insert(const T &val) {
                if (this->count(val) > 0)
                    return;
                if (entry_number * 1.0 / bucket_number >= alpha) {
                    rehash(2 * bucket_number);
                }
                unsigned int id = this->hash(val) % bucket_number;
                (*data)[id].push_back(val);
                ++entry_number;
            }

            // erases elements
            void erase(const T &val) {
                if (this->count(val) == 0)
                    return;
                unsigned int id = this->hash(val) % bucket_number;
                auto iter = Find((*data)[id].begin(), (*data)[id].end(), val, pred);
                (*data)[id].erase(iter);
                --entry_number;
            }

            // clear content
            void clear() {
                for (int i = 0; i < bucket_number; ++i)
                    (*data)[i].clear();
                entry_number = 0;
            }

            HashTable(bool (*_pred)(const T &a, const T &b) = Equal<T>,
                      unsigned long (*_hash)(const T &val) = Hash<T>,
                      double _alpha = 1.0) {
                alpha = _alpha;
                hash = _hash;
                pred = _pred;

                data = new Vector<List<T>>(1);
                bucket_number = 1;
                entry_number = 0;
            }

            ~HashTable() {
                delete data;
            }

        protected:
            Vector<List<T>> *data;
            unsigned int bucket_number, entry_number;
            double alpha;    // congestion control

            unsigned long (*hash)(const T &val);
            bool (*pred)(const T &a, const T &b);

            void rehash(unsigned int new_bucket_number) {
                Vector<List<T>> *temp = new Vector<List<T>>(new_bucket_number);
                for (int i = 0; i < data->size(); ++i) {
                    for (auto iter = (*data)[i].begin(); iter != (*data)[i].end(); ++iter) {
                        T val = *iter;
                        unsigned int id = hash(val) % new_bucket_number;
                        (*temp)[id].push_back(val);
                    }
                }
                delete data;
                data = temp;
                bucket_number = new_bucket_number;
            }
    };
};

#endif
