// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
  char ch;
  int prior;
};

template <typename T>
class TPQueue {
 private:
  struct Node {
    T dataValue;
    Node* nextElement;
    explicit Node(const T& initialData, Node* subsequent = nullptr)
        : dataValue(initialData), nextElement(subsequent) {}
  };

  Node* firstElement;

 public:
  TPQueue() : firstElement(nullptr) {}

  ~TPQueue() {
    while (firstElement) {
      Node* elementToRemove = firstElement;
      firstElement = firstElement->nextElement;
      delete elementToRemove;
    }
  }

  void push(const T& item) {
    Node* newNode = new Node(item);

    if (!firstElement || item.prior > firstElement->dataValue.prior) {
      newNode->nextElement = firstElement;
      firstElement = newNode;
      return;
    }

    Node* currentElement = firstElement;
    while (currentElement->nextElement &&
           item.prior <= currentElement->nextElement->dataValue.prior) {
      currentElement = currentElement->nextElement;
    }

    newNode->nextElement = currentElement->nextElement;
    currentElement->nextElement = newNode;
  }

  T pop() {
    if (!firstElement) {
      throw std::out_of_range("Queue is empty");
    }

    T result = firstElement->dataValue;
    Node* elementToRemove = firstElement;
    firstElement = firstElement->nextElement;
    delete elementToRemove;
    return result;
  }

  bool isEmpty() const { return firstElement == nullptr; }

  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;
};

#endif  // INCLUDE_TPQUEUE_H_
