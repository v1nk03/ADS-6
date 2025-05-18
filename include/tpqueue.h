// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <string>
#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T element;
    Node* next;
    explicit Node(const T& val) : element(val), next(nullptr) {}

    T data;
    Node* link;
    explicit Node(const T& input) : data(input), link(nullptr) {}
  };

  Node* firstNode;
  Node* headNode;

 public:
  TPQueue() : firstNode(nullptr) {}
  TPQueue() : headNode(nullptr) {}

  void push(const T& item) {
    Node* newNode = new Node(item);

    if (firstNode == nullptr || item.prior > firstNode->element.prior) {
      newNode->next = firstNode;
      firstNode = newNode;
  ~TPQueue() {
    while (headNode) {
      Node* temp = headNode;
      headNode = headNode->link;
      delete temp;
    }
  }

  void push(const T& element) {
    Node* newNode = new Node(element);
    if (!headNode) {
      headNode = newNode;
      return;
    }
    if (element.prior > headNode->data.prior) {
        newNode->link = headNode;
        headNode = newNode;
        return;
    }

    Node* traverse = headNode;
    while (traverse->link && traverse->link->data.prior >= element.prior) {
      traverse = traverse->link;
    }
    newNode->link = traverse->link;
    traverse->link = newNode;


  }

  T pop() {
    if (firstNode == nullptr) {
      throw std::string("Queue is empty");
    if (!headNode) {
      throw std::out_of_range("Queue is empty!");
    }

    Node* tempNode = firstNode;
    T returnValue = tempNode->element;
    firstNode = firstNode->next;
    delete tempNode;

    Node* removeNode = headNode;
    T returnValue = headNode->data;
    headNode = headNode->link;
    delete removeNode;
    return returnValue;
  }

  ~TPQueue() {
    while (firstNode != nullptr) {
      Node* toDelete = firstNode;
      firstNode = firstNode->next;
      delete toDelete;
    }
  }
};

struct SYM {
  char ch;
  int prior;
};
#endif  // INCLUDE_TPQUEUE_H_
