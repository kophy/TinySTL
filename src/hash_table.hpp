#ifndef __TINYSTL_HASH_TABLE__
#define __TINYSTL_HASH_TABLE__

#include "vector.hpp"
#include "list.hpp"
#include "allocator.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename T, class Alloc = Allocator<T>>
    class HashTable {
        public:
            // checks whether the hash table is empty
            bool empty() { return (entry_number == 0); }

            // returns the number of elements
            unsigned int size() { return entry_number; }

            // returns the number of elements matching specific key
            unsigned int count(const T &val) {
                unsigned int id = this->hash(val) % bucket_number;
                return Count((*data)[id].begin(), (*data)[id].end(), val, pred);
            }

            // inserts elements
            void insert(const T &val) {
                if (this->count(val) > 0)
                    return;
                if (entry_number * 1.0 / bucket_number >= alpha)
                    rehash(2 * bucket_number);
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

            // constructor
            HashTable(bool (*_pred)(const T &a, const T &b) = Equal<T>, unsigned long (*_hash)(const T &val) = Hash<T>,
                      double _alpha = 1.0) : alpha(_alpha), hash(_hash), pred(_pred) {
                data = new Vector<List<T, Alloc>>(1);
                bucket_number = 1;
                entry_number = 0;
            }

            // destructor
            ~HashTable() { delete data; }

        protected:
            Vector<List<T, Alloc>> *data;
            unsigned int bucket_number, entry_number;
            double alpha;    // congestion control

            unsigned long (*hash)(const T &val);
            bool (*pred)(const T &a, const T &b);

            // TODO: better resize strategy
            void rehash(unsigned int new_bucket_number) {
                auto temp = new Vector<List<T, Alloc>>(new_bucket_number);
                for (int i = 0; i < data->size(); ++i) {
                    for (auto iter = (*data)[i].begin(); iter != (*data)[i].end(); ++iter) {
                        unsigned int id = hash(*iter) % new_bucket_number;
                        (*temp)[id].push_back(*iter);
                    }
                }
                delete data;
                data = temp;
                bucket_number = new_bucket_number;
            }

        public:
            typedef typename List<T>::Iterator list_iter;
            typedef Pair<unsigned int, list_iter> HashEntry;

            HashEntry findBegin() {
                unsigned int id = 0;
                list_iter pos;
                if (this->empty()) {
                    id = bucket_number - 1;
                    pos = (*data).back().end();
                } else {
                    while ((*data)[id].empty())
                        ++id;
                    pos = (*data)[id].begin();
                }
                return MakePair<unsigned int, list_iter>(id, pos);
            }

            HashEntry findEnd() {
                unsigned int id = bucket_number;
                list_iter pos = (*data).back().end();
                return MakePair<unsigned int, list_iter>(id, pos);
            }

            HashEntry findNext(const HashEntry &e) {
                unsigned int id = e.first;
                list_iter pos = e.second;
                ++pos;
                while (pos == (*data)[id].end()) {
                    ++id;
                    if (id == (*data).size())
                        break;
                    pos = (*data)[id].begin();
                }
                return MakePair<unsigned int, list_iter>(id, pos);
            }

            HashEntry find(const T &val) {
                unsigned int id = this->hash(val) % bucket_number;
                for (auto iter = (*data)[id].begin(); iter != (*data)[id].end(); ++iter)
                    if (pred(*iter, val))
                        return MakePair<unsigned int, list_iter>(id, iter);
                return findEnd();
            }
    };
};

#endif
