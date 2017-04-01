#ifndef __TINYSTL_LIST__
#define __TINYSTL_LIST__

#include <stdexcept>
#include <cassert>

namespace TinySTL {
    template <typename T>
    class List {
        public:
            /*** 0. Meta Defintion ***/
            template <typename U>
            struct list_node {
                U val;
                list_node *prev, *next;

                list_node(U _val) : val(_val), prev(nullptr), next(nullptr) {}
            };

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

            template <typename U>
            class Iterator {
                public:
                    bool operator ==(const Iterator<U> &I) {
                        return (this->curr == I.curr);
                    }

                    bool operator !=(const Iterator<U> &I) {
                        return (this->curr != I.curr);
                    }

                    U& operator *() {
                        return curr->val;
                    }

                    Iterator<U> operator ++() {
                        advance();
                        return Iterator<U>(this->curr);
                    }

                    Iterator<U> operator ++(int dummy) {
                        Iterator<U> temp(this->curr);
                        advance();
                        return temp;
                    }

                    Iterator(list_node<U> *_curr = nullptr) : curr(_curr) {}

                private:
                    void advance() {
                        curr = curr->next;
                    }

                    list_node<U> *curr;

                    friend class List;
            };

            // iterator to the beginning
            Iterator<T> begin() {
                return Iterator<T>(head);
            }

            // iterator to the end
            Iterator<T> end() {
                return Iterator<T>(nullptr);
            }

            /*** 3. Capacity ***/
            bool empty() {
                return (N == 0);
            }

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
                auto temp = head;
                head = head->next;
                head->prev = nullptr;
                delete temp;
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
                auto temp = tail;
                tail = tail->prev;
                tail->next = nullptr;
                delete temp;
                --N;
            }

            // insert elements
            void insert(Iterator<T> pos, const T &val) {
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
            Iterator<T> erase(Iterator<T> pos) {
                if (pos == this->end())
                    return pos;
                if (pos == this->begin()) {
                    pop_front();
                } else {
                    list_node<T> *pivot = pos.curr;
                    pivot->prev->next = pivot->next;
                    pivot->next->prev = pivot->prev;
                    pos = Iterator<T>(pivot->next);
                    delete pivot;
                    --N;
                }
                return pos;
            }

            // swap content with another list
            void swap(List<T> &other) {
                auto temp_head = this->head;
                this->head = other.head;
                other.head = temp_head;
                auto temp_tail = this->tail;
                this->tail = other.tail;
                other.tail = temp_tail;
                unsigned int temp_N = this->N;
                this->N = other.N;
                other.N = temp_N;
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

            List() : head(nullptr), tail(nullptr), N(0) {}

            ~List() {
                clear();
            }

        private:
            list_node<T> *head, *tail;

            unsigned int N;
    };
};

#endif
