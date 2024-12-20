#include<bits/stdc++.h>
using namespace std;
template<class T>
class Node {
    private:
        T value;
        Node* prev;
        Node* next;
    public:
        Node(T value, Node* prev, Node* next) {
            value = value;
            prev = prev;
            next = next;
        }
        Node(Node* prev) {
            value = NULL;
            prev = prev;
            next = NULL;
        }
        Node() {
            value = NULL;
            prev = NULL;
            next = NULL;
        }
        bool is_null() {
            return this->value == NULL;
        }
        T unwrap() {
            return this->value;
        }
        Node* get_next() {
            return this->prev;
        }
        Node* get_prev() {
            return this->prev;
        }
};

template<class S>
class Pair {
    private:
        static Pair* sentinel;
        S head;
        Pair* tail;
        Pair() {
            head = NULL;
            tail = NULL;
        }
    public:
        Pair(S head, Pair* tail) {
            head = head;
            tail = tail;
        }
        S get_head() {
            return this->head;
        }
        Pair* get_tail() {
            return this->tail;
        }
        void modify(S new_head) {
            this->head = new_head;
        }
        bool is_null() {
            return this->get_tail == sentinel;
        }
        void map_list(function<S, T>)
};

int main() {

}