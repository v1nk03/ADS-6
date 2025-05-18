// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <stdexcept>

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
    if (!firstElement || item.prior > firstElement->dataValue.prior) {
      firstElement = new Node(item, firstElement);
      return;
    }

    Node* currentElement = firstElement;
    while (currentElement->nextElement &&
           currentElement->nextElement->dataValue.prior >= item.prior) {
      currentElement = currentElement->nextElement;
    }
    currentElement->nextElement = new Node(item, currentElement->nextElement);
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

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
