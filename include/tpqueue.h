// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
    struct Node {
        T payload;
        Node* link;
        explicit Node(const T& data, Node* next = nullptr) : payload(data), link(next) {}
    };

    Node* first;

 public:
    TPQueue() : first(nullptr) {}

    ~TPQueue() {
        while (first) {
            Node* temporary = first;
            first = first->link;
            delete temporary;
        }
    }

    void push(const T& item) {
        if (!first || item.prior > first->payload.prior) {
            first = new Node(item, first);
            return;
        }

        Node* current = first;
        while (current->link && current->link->payload.prior >= item.prior) {
            current = current->link;
        }
        current->link = new Node(item, current->link);
    }

    T pop() {
        if (!first) {
            throw std::out_of_range("Queue is empty");
        }

        T result = first->payload;
        Node* temporary = first;
        first = first->link;
        delete temporary;
        return result;
    }

    bool isEmpty() const {
        return first == nullptr;
    }

    TPQueue(const TPQueue&) = delete;
    TPQueue& operator=(const TPQueue&) = delete;
};

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
