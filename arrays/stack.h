#ifndef STACK_H
#define STACK_H

#include <array>
#include <stdexcept>

template<typename T, int max_size>
class stack {
	using size_type = std::size_t;

public:

	// ctor
	stack();
	
	// access
	T& top();

	const T& top() const
	{ return _array[_size - 1]; }

	// capacity
	bool empty() const
	{ return _size == 0; }

	size_type size() const
	{ return _size; }

	// mutators
	void push(const T& value)
	{
		if (_size == max_size) {
		}
	}

	void push(T&& value)
	{ }

	template<typename... Args>
	void emplace(Args&& ... args)
	{ }

	void pop()
	{ }

	void swap(stack& other) noexcept
	{
		std::swap(_array, other._array);
		std::swap(_size, other._size);
	}

	friend void swap(stack<T, max_size>& lhs, stack<T, max_size>& rhs) noexcept
	{ lhs.swap(rhs); }

private:
	std::array<T, max_size> _array;
	size_type _size;
};

template<typename T, int max_size>
stack<T, max_size>::stack() : _array(), _size(0)
{ }

template<typename T, int max_size>
T& stack<T, max_size>::top()
{ return _array[_size - 1]; }

#endif //STACK_H
