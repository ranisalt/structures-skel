#ifndef STRUCTURES_SKEL_HEAP_H
#define STRUCTURES_SKEL_HEAP_H

#include <functional>
#include "abstract/tree.h"

template<typename T, typename Compare = std::less<T>>
class heap : public tree<T> {
	struct node {
		node(const T& item) : _item(item)
		{ }

		node* _left = nullptr;
		node* _right = nullptr;
		T _item;
	};

public:
	heap() = default;

private:
	size_type _size = 0;
	node* _root = nullptr;
};

#endif //STRUCTURES_SKEL_HEAP_H
