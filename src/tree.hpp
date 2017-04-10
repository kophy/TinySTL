#ifndef __TINYSTL_TREE__
#define __TINYSTL_TREE__

#include "allocator.hpp"
#include "utils.hpp"

namespace TinySTL {
    template <typename U>
    struct tree_node {
        U *pval;
        tree_node *left, *right, *parent;

        tree_node() {
            pval = nullptr;
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }
    };

    template <typename T, class Alloc = Allocator<T>>
    class Tree {
        public:
            // checks whether the tree is empty
            bool empty() {
                return (node_number == 0);
            }

            // returns the number of elements
            unsigned int size() {
                return node_number;
            }

            // returns the number of elements matching specific key
            unsigned int count(const T &val) {
                unsigned int cnt = 0;
                count_helper(cnt, root, val);
                return cnt;
            }

            // insert elements
            void insert(const T &val) {
                insert(root, val);
            }

            // erase elements
            void erase(const T &val) {
                erase(root, val);
            }

            // clear content
            void clear() {
                clear(root);
                root = nullptr;
            }

            Tree(bool (*_cmp)(const T &a, const T &b) = Less<T>) {
                root = nullptr;
                node_number = 0;
                cmp = _cmp;
            }

            ~Tree() {
                clear();
            }

        protected:
            tree_node<T> *root;
            unsigned int node_number;
            Alloc alloc;
            bool (*cmp)(const T &a, const T &b);

            void count_helper(unsigned int &cnt, tree_node<T> *curr, const T &val) {
                if (curr == nullptr)
                    return;
                if (cmp(val, *(curr->pval)))
                    count_helper(cnt, curr->left, val);
                else if (cmp(*(curr->pval), val))
                    count_helper(cnt, curr->right, val);
                else {
                    ++cnt;
                    count_helper(cnt, curr->left, val);
                    count_helper(cnt, curr->right, val);
                }
            }

            void insert(tree_node<T> *curr, const T &val) {
                if (count(val) > 0)
                    return;
                tree_node<T> *new_node = createNode(val);

                ++this->node_number;
                while (curr != nullptr) {
                    new_node->parent = curr;
                    if (cmp(val, *(curr->pval)))
                        curr = curr->left;
                    else
                        curr = curr->right;
                }
                if (new_node->parent == nullptr)
                    this->root = new_node;
                else if (cmp(val, *(new_node->parent->pval)))
                    new_node->parent->left = new_node;
                else
                    new_node->parent->right = new_node;
            }

            void erase(tree_node<T> *curr, const T &val) {
                if (count(val) == 0)
                    return;
                --this->node_number;
                while (true) {
                    if (cmp(val, *(curr->pval)))
                        curr = curr->left;
                    else if (cmp(*(curr->pval), val))
                        curr = curr->right;
                    else
                        break;
                }
                if (curr->left == nullptr || curr->right == nullptr) {
                    tree_node<T> *dummy = (curr->left == nullptr)? curr->right : curr->left;
                    if (dummy != nullptr)
                        dummy->parent = curr->parent;
                    if (curr == curr->parent->left)
                        curr->parent->left = dummy;
                    else
                        curr->parent->right = dummy;
                    deleteNode(curr);
                } else {
                    tree_node<T> *dummy = curr->left;
                    while (dummy->right != nullptr)
                        dummy = dummy->right;
                    if (dummy == dummy->parent->left)
                        dummy->parent->left = nullptr;
                    else
                        dummy->parent->right = nullptr;
                    curr->pval = dummy->pval;
                    deleteNode(dummy);
                }
            }

            void clear(tree_node<T> *curr) {
                if (curr == nullptr)
                    return;
                clear(curr->left);
                clear(curr->right);
                deleteNode(curr);
                --node_number;
            }

            template <class ...Args>
            tree_node<T> *createNode(Args... args) {
                tree_node<T> *p = new tree_node<T>();
                p->pval = alloc.allocate_and_construct(1, args...);
                return p;
            }

            void deleteNode(tree_node<T> *p) {
                alloc.destroy_and_deallocate(p->pval, 1);
                delete p;
            }
    };
};

#endif
