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

template<class T, size_t K>
bool hasPrev(BItreeIt<T, K> it) {
  return it.current->parent != nullptr;
}

template<class T, size_t K>
BItreeIt<T, K> prev(BTreeIt<T, K> it) {
  if (!hasPrev(it)) {
    throw std::logic_error("err");
  }
  return *(it.current->parent);
}

/* всё ниже этой строчки было на паре написано*/
template<class T>
std::pair<size_t, BiTree<T>*> fall_left(BiTree<T>* root) {
  size_t path = 0;
  while(root->lt) {
    root = root->lt;
    path++;
  }
  return {path, root};
}

template<class T>
std::pair<size_t, BiTree<T>*> parent(BiTree<T>* root) {
  size_t path = 0;
  if (!root) {
    return {path, nullptr};
  }
  BiTree<T>* parent = root->parent;
  while (parent && parent->lt != root) {
    path++;
  }
  return {path, parent};
}

template<class T>
bool IsEqualStruct(BiTree<T>* lhs, BiTree<T>* rhs) {
  auto lhs_begin = fall_left(lhs);
  auto rhs_begin = fall_left(rhs);
  if (lhs_begin.first != rhs_begin.first) {
    return 0;
  }
  auto ln = nextStruct(lhs_begin.second);
  auto rn = nextStruct(rhs_begin.second);
  while (std::get<0>(ln) == std::get<0>(rn) &&
    std::get<1>(ln) == std::get<1>(rn) &&
    std::get<2>(ln) == std::get<2>(rn)) {
    ln = nextStruct(std::get<2>(ln));
    rn = nextStruct(std::get<2>(rn));
  }
  return ln == rn;
}

template<class T>
std::tuple<Dir, size_t T, BiTree<T>*> nextStruct(BiTree<T>* root) {
  if (root->rt) {
    auto res = fall_left(root->rt);
    return {Dir::fall_left, result.first, result.second};
  }
  auto result = parent(root);
}

template<class T>
bool includedStructStart(BiTree<T>* lhs_root, BiTree<T>* pattern) {
  auto next_pattern = nextStruct(pattern);
  if (std::get<0>(next_pattern) == Dir::fall_left) {
    auto next_lhs = fall_left(lhs_root);
    if (std::get<1>(next_pattern) != std::get<1>(next_pattern)) {
      return 0;
    } else {
      next_lhs = parent(lhs_root);
    }
    while (std::get<0>(next_pattern) == Dir::fall_left) {
      next_pattern = nextStruct(std::get<2>(next_pattern));
      if (std::get<0>(next_pattern) == Dit::fall_left) {
        next_lhs = fall_left(lhs_root);
      } else {
        next_lhs = parent(lhs_root);
      }
    }
  }
  return !std::get<2>(next_pattern) && std::get<1>(next_pattern) == next_lhs.first;
}

template<class T, class F>
BiTree<T> *minimum(BiTree<T> *root)
{
 if (!root)
 {
  return root;
 }
 while (root->lt)
 {
  root = root->lt;
 }
 return root;
}

template<class T, class F>
F traverse(BiTree<T> *root, F f)
{
 if (!root)
 {
  return f;
 }
 BiTree<T> *next = minimum(root);
 while (next)
 {
  f(next->val);
  if (next->rt)
  {
   next = next->rt;
   next = minimum(next);
  }
  else
  {
   BiTree<T> *parent = next->parent;
   while (parent && parent->lt == next)
   {
    next = parent;
    parent = parent->parent;
   }
  }
 }
 return f;
}

template<class T>
bool hasnext(BiTree<T> *root) {
 return root->lt || root->rt;
}

template<class T>
bool hasparent(BiTree<T> *root) {
 return root->parent;
}
template<class T>
struct TriTree {
 T val0, val1;
 TriTree<T> *lt, *rt, *mid, *parent;
};

template<class T>
struct TriTreeIt {
 size_t s;
 TriTree<T> *curr;
};

template<class T>
T& value(TriTreeIt<T> it) {
 return it.curr->val;
}

template<class T>
bool hasNext(TriTreeIt<T> it) {
 return it.curr->lt || it.curr->rt || it.curr->mid;
}

template<class T>
bool hasPrev(TriTreeIt<T> it) {
 return it.curr->parent;
}

template<class T>
TriTreeIt<T> next(TriTreeIt<T> it) {
 if (hasNext(it)) {
  return (it.curr->lt == nullptr ? it.curr->lt : it.curr->mid == nullptr ? it.curr->mid : it.curr->rt);
 }
 return it;
}

template<class T>
TriTreeIt<T> prev(TriTreeIt<T> it) {
 if (hasPrev(it)) {
  return it.curr->parent;
 }
 return it;
}

template< class T >
std::tuple< BiTree< T >*, BiTree< T >*, bool> isEqualStructStart(BiTree< T >* lhs_start, BiTree< T >* rhs_start)
{
  auto ln = nextStruct(lhs_start);
  auto rn = nextStruct(rhs_start);
  while (std::get< 0 >(ln) == std::get< 0 >(rn) &&
      std::get< 1 >(ln) == std::get< 1 >(rn) &&
      std::get< 2 >(ln) && std::get< 2 >(rn)) {
    ln = nextStruct(std::get< 2 >(ln));
    rn = nextStruct(std::get< 2 >(rn));
  }
  bool dir = std::get< 0 >(ln) == std::get< 0 >(rn);
  return {std::get< 2 >(ln), std::get< 2 >(rn), dir};
}

template< class T >
bool includedStruct(BiTree<T>* lhs, BiTree<T>* pattern)
{
  BiTree< T >* lhs = fallLeft(lhs).second;
  while (lhs) {
    auto result = isEqualStructStart(lhs, fallLeft(pattern).second));
    if (!std::get< 1 >(result) && std::get< 2 >(result)) {
      return true;
    }
    lhs = nextStruct(lhs).second;
  }
  return false;
}

template< class T >
bool isEqualStruct(BiTree< T >* lhs, BiTree< T >* rhs)
{
  auto lhs_begin = fallLeft(lhs);
  auto rhs_begin = fallLeft(rhs);
  if (lhs_begin.first != rhs_begin.first) {
    return false;
  }
  auto result = isEqualStructStart(lhs_begin.second, rhs_begin.second);
  return !std::get< 0 >(result) && !std::get< 1 >(result);
}

template< class T >
std::pair< BiTree<T>*, BiTree<T>* >
inclusion(
  BiTree<T>* lhs,
  BiTree<T>* pattern
)
{
  BiTree< T >* lhs_curr = fall_left(lhs).second;
  while (lhs_curr) {
    auto result = isEqualStructStart(lhs_curr, fallLeft(pattern).second));
    if (!std::get< 1 >(result) && std::get< 2 >(result)) {
      BiTree< T >* last_lhs_next = std::get< 0 >(result);
      if (!last_lhs_next) {
        BiTree< T >* lhs_end = lhs;
        while (lhs_end->rt) {
          lhs_end = lhs_end->rt;
        }
        return {lhs_curr, lhs_end};
      }
      BiTree< T >* lhs_end = prev(last_lhs_next);
      return {lhs_curr, lhs_end};
    }
    lhs_curr = nextStruct(lhs_curr).second;
  }
  return false; 
}

template< class T >
BiTree< T >* prev(BiTree< T >* curr)
{
  BiTree< T >* next = curr;
  if (next->lt) {
    next = next->lt;
    while (next->rt) {
      next = next->tr;
    }
  } else {
    BiTree< T >* parent = next->parent;
    while (parent && parent->rt != next) {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return next;
}

template< class T > struct InclusionIt {
  std::pair< BiTree<T>*, BiTree<T>* > incl;
};
template< class T >
InclusionIt<T> begin(BiTree<T>* lhs, BiTree<T>* pattern);

template< class T >
InclusionI<T> next(InclusionIt<T> curr, BiTree< T >* pattern);

template< class T >
bool hasNext(InclusionIt<T> curr, BiTree< T >* pattern);