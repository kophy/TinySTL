#ifndef __TINYSTL_TREE_SET__
#define __TINYSTL_TREE_SET__

#include "tree.hpp"
#include "allocator.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename T, class Alloc = Allocator<T>>
    class TreeSet : public Tree<T, Alloc> {
        public:
            class Iterator : public ForwardIterator {
                public:
                    bool operator ==(const Iterator &I) { return this->curr == I.curr; }
                    bool operator !=(const Iterator &I) { return this->curr != I.curr; }

                    const T &operator *() { return *(curr->pval); }

                    Iterator operator ++() {
                        advance();
                        return *this;
                    }

                    Iterator operator ++(int dummy) {
                        auto temp = *this;
                        advance();
                        return temp;
                    }

                    Iterator(tree_node<T> *_curr = nullptr) : curr(_curr) {}

                private:
                    tree_node<T> *curr;

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

                friend class TreeSet<T>;
            };

            class ReverseIterator : public BackwardIterator {
                public:
                    bool operator ==(const ReverseIterator &I) { return this->curr == I.curr; }
                    bool operator !=(const ReverseIterator &I) { return this->curr != I.curr; }

                    const T &operator *() { return *(curr->pval); }

                    ReverseIterator operator ++() {
                        advance();
                        return *this;
                    }

                    ReverseIterator operator ++(int dummy) {
                        auto temp = *this;
                        advance();
                        return temp;
                    }

                    ReverseIterator(tree_node<T> *_curr = nullptr) : curr(_curr) {}

                private:
                    tree_node<T> *curr;

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

                friend class TreeSet<T>;
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
            Iterator find(const T &val) {
                tree_node<T> *curr = base::root;
                while (curr != nullptr) {
                    if (base::cmp(val, *(curr->pval)))
                        curr = curr->left;
                    else if (base::cmp(*(curr->pval), val))
                        curr = curr->right;
                    else
                        return Iterator(curr);
                }
                return this->end();
            }

            TreeSet(bool (*_cmp)(const T &a, const T &b) = Less<T>) : Tree<T>::Tree(_cmp) {}

        private:
            typedef Tree<T> base;

        friend class Iterator;
        friend class ReverseIterator;
    };
};

#endif
