// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <string>
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;

    explicit Node(const T& input) : data(input), next(nullptr) {}
  };

  Node* headNode;

 public:
  TPQueue() : headNode(nullptr) {}

  ~TPQueue() {
    while (headNode) {
      Node* temp = headNode;
      headNode = headNode->next;
      delete temp;
    }
  }

  void push(const T& element) {
    Node* newNode = new Node(element);

    if (!headNode || element.prior > headNode->data.prior) {
      newNode->next = headNode;
      headNode = newNode;
      return;
    }

    Node* iterator = headNode;
    while (iterator->next && iterator->next->data.prior >= element.prior) {
      iterator = iterator->next;
    }
    newNode->next = iterator->next;
    iterator->next = newNode;
  }

  T pop() {
    if (!headNode) {
      throw std::out_of_range("Queue is empty!");
    }

    Node* removeNode = headNode;
    T returnValue = headNode->data;
    headNode = headNode->next;
    delete removeNode;
    return returnValue;
  }
};

struct SYM {
  int prior; // 'ch' removed because it's unused.
};

#endif  // INCLUDE_TPQUEUE_H_
