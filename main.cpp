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
  BiTree<T>* parent = root->parent;
  while (parent && parent->lt != root) {
    path++;
  }
  return {path, parent};
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
