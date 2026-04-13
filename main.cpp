template<class T, size_t K>
struct BTree {
	T val[K];
	BTree<T, K>*	childs[K + 1];
	BTree<T, K>*	parent;
};

template<class T, size_t K>
struct BTreeIt {
	size_t s;
	BTree<T, K>* current;
};

template<class T, size_t K>
T value(BTree<T, K> it) {

}
