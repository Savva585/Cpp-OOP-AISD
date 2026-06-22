#include <iostream>
#include<random>
#include<vector>
using namespace std;
struct stats {
  size_t comparison_count = 0;
  size_t copy_count = 0;
};
template<typename T>
struct Node {
  T _value;
  Node<T>* next;
  Node<T>* prev;
  Node(T value) : _value(value) {
    this->next = nullptr;
    this->prev = nullptr;
  }
};
template<typename T>
class list {
  Node<T>* head;
  Node<T>* tail;
public:
  list() {
    this->head = this->tail = nullptr;
  }

  list(const list& other) : head(nullptr), tail(nullptr) {
    if (other.head != nullptr) {
      Node<T>* current = other.head;
      do {
        push_tail(current->_value);
        current = current->next;
      } while (current != other.head);
    }
  }

  list(size_t n, T start, T end) : head(nullptr), tail(nullptr) {
    if (n == 0) return;

    random_device device;
    uniform_int_distribution<T> distr(min(start, end), max(start, end));

    for (size_t i = 0; i < n; i++) {
      push_tail(distr(device));
    }
  }

  void clear() {
    if (head == nullptr) return;

    Node<T>* current = head;
    do {
      Node<T>* next = current->next;
      delete current;
      current = next;
    } while (current != head);

    head = nullptr;
    tail = nullptr;
  }

  ~list() {
    clear();
  }

  friend void reverse<>(list<T>& ls);

  Node<T>* push_tail(const T value) {
    Node<T>* ptr = new Node<T>(value);
    if (head == nullptr) {
      head = ptr;
      tail = ptr;
      ptr->next = ptr;
      ptr->prev = ptr;
    }
    else {
      ptr->prev = tail;
      ptr->next = head;
      tail->next = ptr;
      head->prev = ptr;
      tail = ptr;
    }
    return ptr;
  }

  Node<T>* push_head(const T value) {
    Node<T>* ptr = new Node<T>(value);
    if (head == nullptr) {
      head = ptr;
      tail = ptr;
      ptr->next = ptr;
      ptr->prev = ptr;
    }
    else {
      ptr->next = head;
      ptr->prev = tail;
      head->prev = ptr;
      tail->next = ptr;
      head = ptr;
    }
    return ptr;
  }

  void pop_head() {
    if (head == nullptr) return;

    if (head == tail) {
      delete head;
      head = nullptr;
      tail = nullptr;
    }
    else {
      Node<T>* new_head = head->next;
      tail->next = new_head;
      new_head->prev = tail;
      delete head;
      head = new_head;
    }
  }

  void pop_tail() {
    if (tail == nullptr) return;

    if (head == tail) {
      delete tail;
      head = nullptr;
      tail = nullptr;
    }
    else {
      Node<T>* new_tail = tail->prev;
      new_tail->next = head;
      head->prev = new_tail;
      delete tail;
      tail = new_tail;
    }
  }

  size_t size() const {
    if (head == nullptr) return 0;

    size_t count = 0;
    Node<T>* current = head;
    do {
      count++;
      current = current->next;
    } while (current != head);

    return count;
  }

  bool empty() const {
    return head == nullptr;
  }

  Node<T>* front() const { return head; }
  Node<T>* back() const { return tail; }

  Node<T>* get_value(size_t index) {
    if (head == nullptr) return nullptr;

    Node<T>* ptr = head;
    size_t cnt = 0;

    do {
      if (cnt == index) return ptr;
      ptr = ptr->next;
      cnt++;
    } while (ptr != head && cnt <= index);

    return nullptr;
  }

  T& operator[](size_t index) {
    Node<T>* node = get_value(index);
    if (node == nullptr) {
      throw std::out_of_range("Index out of range");
    }
    return node->_value;
  }

  T operator[](size_t index) const {
    Node<T>* node = get_value(index);
    if (node == nullptr) {
      throw std::out_of_range("Index out of range");
    }
    return node->_value;
  }

  list& operator=(const list& rhs) {
    if (this != &rhs) {
      clear();
      if (rhs.head != nullptr) {
        Node<T>* rhs_current = rhs.head;
        do {
          push_tail(rhs_current->_value);
          rhs_current = rhs_current->next;
        } while (rhs_current != rhs.head);
      }
    }
    return *this;
  }

  void push_tail(list& linked_list) {
    if (linked_list.head == nullptr) {
      return;
    }
    if (this->head == nullptr) {
      this->head = linked_list.head;
      this->tail = linked_list.tail;
      this->tail->next = this->head;
      this->head->prev = this->tail;
    }
    else {
      this->tail->next = linked_list.head;
      linked_list.head->prev = this->tail;
      linked_list.tail->next = this->head;
      this->head->prev = linked_list.tail;
      this->tail = linked_list.tail;
    }
    linked_list.head = nullptr;
    linked_list.tail = nullptr;
  }

  void push_head(list& linked_list) {
    if (linked_list.head == nullptr) {
      return;
    }
    if (this->head == nullptr) {
      this->head = linked_list.head;
      this->tail = linked_list.tail;
      this->tail->next = this->head;
      this->head->prev = this->tail;
    }
    else {
      linked_list.tail->next = this->head;
      this->head->prev = linked_list.tail;
      this->tail->next = linked_list.head;
      linked_list.head->prev = this->tail;
      this->head = linked_list.head;
    }
    linked_list.head = nullptr;
    linked_list.tail = nullptr;
  }
  void swap(Node<int>* a, Node<int>* b, stats& result) {
    if (!a || !b || a == b) return;

    int temp = a->_value;
    a->_value = b->_value;
    b->_value = temp;

    result.copy_count += 3;
  }
};




template<typename T>
ostream& operator<<(ostream& os, const list<T>& lst) {
  if (lst.front() == nullptr) {
    os << "[]";
    return os;
  }

  Node<T>* current = lst.front();
  os << "[";
  do {
    os << current->_value;
    current = current->next;
    if (current != lst.front()) {
      os << " <-> ";
    }
  } while (current != lst.front());
  os << "]";
  return os;
}

template <class T>
void reverse(list<T>& ls)
{
  if (ls.head == nullptr) return;

  Node<T>* tmp = ls.head;
  do {
    swap(tmp->next, tmp->prev);
    tmp = tmp->prev;
  } while (tmp != ls.head);
  swap(ls.head, ls.tail);
}
