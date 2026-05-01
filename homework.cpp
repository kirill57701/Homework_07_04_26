template<class T, size_t K>
struct BTree {
  T val[K];
  BTree<T, K>* childs[K + 1];
  BTree<T, K>* parent;
};


template< class T > struct InclusionIt {
  std::pair< BiTree<T>*, BiTree<T>* > incl;
};
template< class T >
InclusionIt<T> begin(BiTree<T>* lhs, BiTree<T>* pattern);

template< class T >
InclusionI<T> next(InclusionIt<T> curr, BiTree< T >* pattern);

template< class T >
bool hasNext(InclusionIt<T> curr, BiTree< T >* pattern);

template< class T > struct InclusionIt {
  std::pair< BiTree<T>*, BiTree<T>* > incl;
};

template< class T >
InclusionIt<T> begin(BiTree<T>* lhs, BiTree<T>* pattern)
{
  BiTree< T >* beg = fallLeft(lhs).second;
  InclusionIt<T> res = inclusionStart(beg, pattern);
  return res;
}

template< class T >
InclusionIt<T> next(InclusionIt<T> curr, BiTree< T >* pattern)
{
  if (!curr.incl.first) {
    auto res = make_pair(nullptr, nullptr);
    return res;
  }

  BiTree< T >* nexs = nextStruct(curr.incl.first).second;
  InclusionIt<T> res = inclusionStart(nexs, pattern);
  return res;
}

template< class T >
bool hasNext(InclusionIt<T> curr, BiTree< T >* pattern)
{
  return curr.incl.first != nullptr;
}
