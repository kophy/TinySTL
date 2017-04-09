#ifndef __TINYSTL_LIST__
#define __TINYSTL_LIST__

#include <stdexcept>
#include "utils.hpp"

namespace TinySTL {
    template <typename U>
    struct list_node {
        U val;
        list_node *prev, *next;

        list_node(U _val) : val(_val), prev(nullptr), next(nullptr) {}
    };

    template <typename T>
    class List {
        public:
            /*** 1. Element Access ***/

            // access first element
            T &front() {
                if (head == nullptr)
                    throw std::out_of_range("empty list");
                return head->val;
            }

            // access last element
            T &back() {
                if (tail == nullptr)
                    throw std::out_of_range("empty list");
                return tail->val;
            }

            /*** 2. Iterator ***/

            class Iterator : public ForwardIterator {
                public:
                    bool operator ==(const Iterator &I) {
                        return (this->curr == I.curr);
                    }

                    bool operator !=(const Iterator &I) {
                        return (this->curr != I.curr);
                    }

                    T &operator *() {
                        return curr->val;
                    }

                    Iterator operator ++() {
                        advance();
                        return Iterator(this->curr);
                    }

                    Iterator operator ++(int dummy) {
                        Iterator temp(this->curr);
                        advance();
                        return temp;
                    }

                    Iterator(list_node<T> *_curr = nullptr) : curr(_curr) {}

                private:
                    void advance() {
                        curr = curr->next;
                    }

                    list_node<T> *curr;

                friend class List<T>;
            };

            class ReverseIterator : public BackwardIterator {
                public:
                    bool operator ==(const ReverseIterator &I) {
                        return (this->curr == I.curr);
                    }

                    bool operator !=(const ReverseIterator &I) {
                        return (this->curr != I.curr);
                    }

                    T &operator *() {
                        return curr->val;
                    }

                    ReverseIterator operator ++() {
                        advance();
                        return ReverseIterator(this->curr);
                    }

                    ReverseIterator operator ++(int dummy) {
                        ReverseIterator temp(this->curr);
                        advance();
                        return temp;
                    }

                    ReverseIterator(list_node<T> *_curr = nullptr) : curr(_curr) {}

                private:
                    void advance() {
                        curr = curr->prev;
                    }

                    list_node<T> *curr;

                friend class List<T>;
            };

            // iterator to the beginning
            Iterator begin() {
                return Iterator(head);
            }

            // iterator to the end
            Iterator end() {
                return Iterator(nullptr);
            }

            // reverse iterator to the beginning
            ReverseIterator rbegin() {
                return ReverseIterator(tail);
            }

            // reverse iterator to the end
            ReverseIterator rend() {
                return ReverseIterator(nullptr);
            }

            /*** 3. Capacity ***/

            // checks whether the list is empty
            bool empty() {
                return (N == 0);
            }

            // returns the number of elements
            unsigned int size() {
                return N;
            }

            /*** 4. Modifiers ***/

            // add element at beginning
            void push_front(const T &val) {
                if (this->empty()) {
                    head = new list_node<T>(val);
                    tail = head;
                } else {
                    head->prev = new list_node<T>(val);
                    head->prev->next = head;
                    head = head->prev;
                }
                ++N;
            }

            // delete first element
            void pop_front() {
                if (head == nullptr)
                    throw std::out_of_range("empty list");
                if (N == 1) {
                    delete head;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    auto temp = head;
                    head = head->next;
                    head->prev = nullptr;
                    delete temp;
                }
                --N;
            }

            // add element at end
            void push_back(const T &val) {
                if (this->empty()) {
                    head = new list_node<T>(val);
                    tail = head;
                } else {
                    tail->next = new list_node<T>(val);
                    tail->next->prev = tail;
                    tail = tail->next;
                }
                ++N;
            }

            // delete last element
            void pop_back() {
                if (tail == nullptr)
                    throw std::out_of_range("empty list");
                if (N == 1) {
                    delete head;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    auto temp = tail;
                    tail = tail->prev;
                    tail->next = nullptr;
                    delete temp;
                    --N;
                }
            }

            // insert elements
            void insert(Iterator pos, const T &val) {
                if (pos == this->begin()) {
                    push_front(val);
                } else if (pos == this->end()) {
                    push_back(val);
                } else {
                    list_node<T> *pivot = pos.curr;
                    list_node<T> *new_node = new list_node<T>(val);
                    pivot->prev->next = new_node;
                    new_node->prev = pivot->prev;
                    new_node->next = pivot;
                    pivot->prev = new_node;
                    ++N;
                }
            }

            // erase elements
            Iterator erase(Iterator pos) {
                if (pos == this->end())
                    return pos;
                if (pos == this->begin()) {
                    pop_front();
                    return this->begin();
                }  else {
                    list_node<T> *pivot = pos.curr;
                    pivot->prev->next = pivot->next;
                    pivot->next->prev = pivot->prev;
                    pos = Iterator(pivot->next);
                    delete pivot;
                    --N;
                    return pos;
                }
            }

            // swap content with another list
            void swap(List<T> &other) {
                Swap(this->head, other.head);
                Swap(this->tail, other.tail);
                Swap(this->N, other.N);
            }

            // clear content
            void clear() {
                while (N > 0) {
                    auto rest = head->next;
                    delete head;
                    head = rest;
                    --N;
                }
                head = nullptr;
                tail = nullptr;
            }

            /*** 5. Constructor and Destructor ***/

            // constructor
            List() : head(nullptr), tail(nullptr), N(0) {}

            // destructor
            ~List() {
                clear();
            }

        private:
            list_node<T> *head, *tail;
            unsigned int N;

        friend class Iterator;
        friend class ReverseIterator;
    };
};

#endif
