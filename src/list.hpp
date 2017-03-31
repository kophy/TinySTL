#ifndef __TINYSTL_LIST__
#define __TINYSTL_LIST__

#include <stdexcept>

namespace TinySTL {
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

            /*** TODO: 2. Iterator ***/

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
            template <typename U>
            struct list_node {
                U val;
                list_node *prev, *next;

                list_node(U _val) : val(_val), prev(nullptr), next(nullptr) {}
            };

            list_node<T> *head, *tail;

            unsigned int N;
    };
};

#endif
