#ifndef __TINYSTL_TREE_MAP__
#define __TINYSTL_TREE_MAP__

#include "tree.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename Key, typename Value>
    static bool compareKey(const Pair<const Key, Value> &a, const Pair<const Key, Value> &b) {
        return a.first < b.first;
    }

    template <typename Key, typename Value, class Alloc = Allocator<Pair<const Key, Value>>>
    class TreeMap : public Tree<Pair<const Key, Value>, Alloc> {
        public:
            class Iterator : public ForwardIterator {
                public:
                    bool operator ==(const Iterator &I) { return this->curr == I.curr; }
                    bool operator !=(const Iterator &I) { return this->curr != I.curr; }

                    Pair<const Key, Value> &operator *()  { return *(curr->pval); }
                    Pair<const Key, Value> *operator ->() { return curr->pval; }

                    Iterator operator ++() {
                        advance();
                        return *this;
                    }

                    Iterator operator ++(int dummy) {
                        auto temp = *this;
                        advance();
                        return temp;
                    }

                    Iterator(tree_node<Pair<const Key, Value>> *_curr = nullptr) : curr(_curr) {}

                private:
                    tree_node<Pair<const Key, Value>> *curr;

                    void advance() {
                        if (curr->right != nullptr) {
                            curr = curr->right;
                            while (curr->left != nullptr)
                                curr = curr->left;
                        } else {
                            auto next = curr->parent;
                            while (next != nullptr && curr == next->right) {
                                curr = next;
                                next = next->parent;
                            }
                            curr = next;
                        }
                    }

                friend class TreeMap<Key, Value>;
            };

            class ReverseIterator : public BackwardIterator {
                public:
                    bool operator ==(const ReverseIterator &I) { return this->curr == I.curr; }
                    bool operator !=(const ReverseIterator &I) { return this->curr != I.curr; }

                    Pair<const Key, Value> &operator *()  { return *(curr->pval); }
                    Pair<const Key, Value> *operator ->() { return curr->pval; }

                    ReverseIterator operator ++() {
                        advance();
                        return *this;
                    }

                    ReverseIterator operator ++(int dummy) {
                        auto temp = *this;
                        advance();
                        return temp;
                    }

                    ReverseIterator(tree_node<Pair<const Key, Value>> *_curr = nullptr) : curr(_curr) {}

                private:
                    tree_node<Pair<const Key, Value>> *curr;

                    void advance() {
                        if (curr->left != nullptr) {
                            curr = curr->left;
                            while (curr->right != nullptr)
                                curr = curr->right;
                        } else {
                            auto next = curr->parent;
                            while (next != nullptr && curr == next->left) {
                                curr = next;
                                next = next->parent;
                            }
                            curr = next;
                        }
                    }

                friend class TreeMap<Key, Value>;
            };

            // iterator to the beginning
            Iterator begin() {
                auto curr = base::root;
                if (curr != nullptr)
                    while (curr->left != nullptr)
                        curr = curr->left;
                return Iterator(curr);
            }

            // iterator to the end
            Iterator end() { return Iterator(); }

            // reverse iterator to the beginning
            ReverseIterator rbegin() {
                auto curr = base::root;
                if (curr != nullptr)
                    while (curr->right != nullptr)
                        curr = curr->right;
                return ReverseIterator(curr);
            }

            // reverse iterator to the end
            ReverseIterator rend() { return ReverseIterator(); }

            // iterator to element with specific key
            Iterator find(const Key &k) {
                auto kv = MakePair<const Key, Value>(k, Value());
                auto curr = base::root;
                while (curr != nullptr) {
                    if (base::cmp(kv, *(curr->pval)))
                        curr = curr->left;
                    else if (base::cmp(*(curr->pval), kv))
                        curr = curr->right;
                    else
                        return Iterator(curr);
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
                base::insert(MakePair<const Key, Value>(k, v));
            }

            // erase wrapper
            void erase(const Key &k) {
                base::erase(MakePair<const Key, Value>(k, Value()));
            }

            // count wrapper
            unsigned int count(const Key &k) {
                return base::count(MakePair<const Key, Value>(k, Value()));
            }

            TreeMap(bool (*_cmp)(const Pair<const Key, Value> &a, const Pair<const Key, Value> &b) = compareKey) :
                Tree<Pair<const Key, Value>, Alloc>::Tree(_cmp) {}

        private:
            typedef Tree<Pair<const Key, Value>> base;

        friend class Iterator;
        friend class ReverseIterator;
    };
};

#endif
