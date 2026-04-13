#include <cstddef>
#include <stdexcept>

template<class T, size_t K>
struct BTree {
  T val[K];
  BTree<T, K>* childs[K + 1];
  BTree<T, K>* parent;
};

template<class T, size_t K>
struct BTreeIt {
  size_t s;
  BTree<T, K>* current;
};

template<class T, size_t K>
T value(BTreeIt<T, K> it) {
  if (it.current == nullptr || it.s >= K) {
    throw std::logic_error();
  }
  return it.current->val[it.s];
}

template<class T, size_t K>
bool hasNext(BTreeIt<T, K> it) {
  if (it.current == nullptr || it.s +1 >= K) {
    return 0;
  }
  if (it.s + 1 < K) {
    return 1;
  }
  if (it.current->childs[it.s + 1] != nullptr) {
    return 1;
  }
  return 0;
}

template<class T, size_t K>
BTreeIt<T, K> next(BTreeIt<T, K> it) {
  if (it.current == nullptr || it.s > K) {
    throw std::logic_error();
  }
  if (!hasNext(it)) {
    return nullptr;
  }
  if (it.s + 1 < K) {
    return it.current->val[++it.s];
  }
  for (size_t i = 0; i < K + 1; ++i) {
    if (it.current->childs[i] != nullptr) {
      return *(it.current->childs[i]);
    }
  }
  return *(it.current->childs[K]);
}
