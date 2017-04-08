#ifndef __TINYSTL_TREE__
#define __TINYSTL_TREE__

#include "utils.hpp"

namespace TinySTL {
    template <typename T>
    class Tree {
        public:
            template <typename U>
            struct tree_node {
                U val;
                tree_node *left, *right, *parent;

                tree_node(U _val) : val(_val), left(nullptr), right(nullptr), parent(nullptr) {}
            };

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
                return count(root, val);
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

        private:
            tree_node<T> *root;
            unsigned int node_number;
            bool (*cmp)(const T &a, const T &b);

            unsigned int count(tree_node<T> *curr, const T &val) {
                while (curr != nullptr) {
                    if (cmp(val, curr->val))
                        curr = curr->left;
                    else if (cmp(curr->val, val))
                        curr = curr->right;
                    else
                        return 1;
                }
                return 0;
            }

            void insert(tree_node<T> *curr, const T &val) {
                if (count(root, val) > 0)
                    return;
                tree_node<T> *new_node = new tree_node<T>(val);
                ++this->node_number;
                while (curr != nullptr) {
                    new_node->parent = curr;
                    if (cmp(val, curr->val))
                        curr = curr->left;
                    else
                        curr = curr->right;
                }
                if (new_node->parent == nullptr)
                    this->root = new_node;
                else if (cmp(val, new_node->parent->val))
                    new_node->parent->left = new_node;
                else
                    new_node->parent->right = new_node;
            }

            void erase(tree_node<T> *curr, const T &val) {
                if (count(root, val) == 0)
                    return;
                --this->node_number;
                while (true) {
                    if (cmp(val, curr->val))
                        curr = curr->left;
                    else if (cmp(curr->val, val))
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
                    delete curr;
                } else {
                    tree_node<T> *dummy = curr->left;
                    while (dummy->right != nullptr)
                        dummy = dummy->right;
                    if (dummy == dummy->parent->left)
                        dummy->parent->left = nullptr;
                    else
                        dummy->parent->right = nullptr;
                    curr->val = dummy->val;
                    delete dummy;
                }
            }

            void clear(tree_node<T> *curr) {
                if (curr == nullptr)
                    return;
                clear(curr->left);
                clear(curr->right);
                delete curr;
                --node_number;
            }
    };
};

#endif
