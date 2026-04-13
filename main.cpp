#include <cstddef>
#include <stdexcept>

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
T value(BTreeIt<T, K> it) {
	if (it.current == nullptr || it.s > K) {
		throw std::logic_error();
	}
	return it.current->val[it.s];
}

template<class T, size_t K>
bool hasNext(BTreeIt<T, K> it) {
	if (it.current == nullptr || s > K) {
		throw std::logic_error();
	}
	if (it.s < K) {
		return 1;
	}
	for (size_t i = 0; i < K +1; ++i) {
		if (it.current->childs[i] != nullptr) {
			return 1;
		}
	}
	return 0;
}

/*template<class T, size_t K>
BTreeIt<T, K> next(BTreeIt<T, K> it) {
	if (it.current == nullptr || it.s > K) {
		throw std::logic_error();
	}
	if (it.s < K) {
		return it.current->val[++it.s];
	}

}*/
