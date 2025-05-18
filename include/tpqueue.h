// Copyright 2022 NNTU-CS
// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cstddef>
#include <utility>

// A singly‑linked list based priority queue.
// Insertion:  O(n)
// Removal:    O(1)

template <typename T>
class TPQueue {
 public:
  TPQueue() : head_node_(nullptr) {}
  TPQueue(const TPQueue& other) : head_node_(nullptr) { CopyFrom(other); }
  TPQueue& operator=(const TPQueue& other) {
    if (this != &other) {
      Clear();
      CopyFrom(other);
    }
    return *this;
  }

  TPQueue(TPQueue&& other) noexcept : head_node_(other.head_node_) { other.head_node_ = nullptr; }

  TPQueue& operator=(TPQueue&& other) noexcept {
    if (this != &other) {
      Clear();
      head_node_ = other.head_node_;
      other.head_node_ = nullptr;
    }
    return *this;
  }

  ~TPQueue() { Clear(); }

  bool empty() const { return head_node_ == nullptr; }

  void push(const T& value) {
    Node* new_node = new Node(value);

    if (empty() || value.prior > head_node_->data.prior) {
      new_node->next_node_ = head_node_;
      head_node_ = new_node;
      return;
    }

    Node* previous_node = head_node_;
    while (previous_node->next_node_ != nullptr &&
           previous_node->next_node_->data.prior >= value.prior) {
      previous_node = previous_node->next_node_;
    }

    new_node->next_node_ = previous_node->next_node_;
    previous_node->next_node_ = new_node;
  }

  T pop() {
    if (empty()) {
      return T{};  // For the purpose of laboratory tests we return default value.
    }

    Node* node_to_delete = head_node_;
    head_node_ = head_node_->next_node_;
    T result = node_to_delete->data;
    delete node_to_delete;
    return result;
  }
 private:
  struct Node {
    explicit Node(const T& d) : data(d), next_node_(nullptr) {}
    T data;
    Node* next_node_;
  };
  Node* head_node_;
  void Clear() {
    while (!empty()) {
      pop();
    }
  }
  void CopyFrom(const TPQueue& other) {
    if (other.empty()) return;
    head_node_ = new Node(other.head_node_->data);
    Node* destination_current = head_node_;
    Node* source_current = other.head_node_->next_node_;
    while (source_current != nullptr) {
      destination_current->next_node_ = new Node(source_current->data);
      destination_current = destination_current->next_node_;
      source_current = source_current->next_node_;
    }
  }
};

struct SYM {
  char ch;
  int prior;
};
#endif  // INCLUDE_TPQUEUE_H_
