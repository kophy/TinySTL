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

                    void advance() { curr = findSuccessor(curr); }

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

                    void advance() { curr = findPrecursor(curr); }

                friend class TreeSet<T>;
            };

            // iterator to the beginning
            Iterator begin() { return Iterator(base::findLeftmost()); }

            // iterator to the end
            Iterator end()   { return Iterator(); }

            // reverse iterator to the beginning
            ReverseIterator rbegin() { return ReverseIterator(base::findRightmost()); }

            // reverse iterator to the end
            ReverseIterator rend()   { return ReverseIterator(); }

            // iterator to element with specific key
            Iterator find(const T &val) { return Iterator(base::find(val)); }

            TreeSet(bool (*_cmp)(const T &a, const T &b) = Less<T>) : Tree<T>::Tree(_cmp) {}

        private:
            typedef Tree<T> base;

        friend class Iterator;
        friend class ReverseIterator;
    };
};

#endif
