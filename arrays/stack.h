#ifndef STACK_H
#define STACK_H

#include <array>
#include <stdexcept>

template<typename T, int max_size>
class stack {
	using size_type = std::size_t;

public:

	// ctor
	stack() = default;

	// access
	T& top();

	const T& top() const;

	// capacity
	bool empty() const noexcept;

	size_type size() const noexcept;

	// mutators
	void push(const T& value);

	void push(T&& value);

	template<typename... Args>
	void emplace(Args&& ... args);

	void pop();

	void swap(stack& other) noexcept;

	friend void swap(stack<T, max_size>& lhs, stack<T, max_size>& rhs) noexcept
	{ lhs.swap(rhs); }

private:
	std::array<T, max_size> _array;
	size_type _size = 0;
};

template<typename T, int max_size>
T& stack<T, max_size>::top()
{
	return _array.at(_size - 1);
}

template<typename T, int max_size>
const T& stack<T, max_size>::top() const
{
	return top();
}

template<typename T, int max_size>
bool stack<T, max_size>::empty() const noexcept
{
	return _size == 0;
}

template<typename T, int max_size>
typename stack<T, max_size>::size_type stack<T, max_size>::size() const noexcept
{
	return _size;
}

template<typename T, int max_size>
void stack<T, max_size>::push(const T& value)
{
	if (_size < max_size) {
		_array[_size] = value;
		++_size;
	} else {
		throw std::out_of_range("Stack is full.");
	}
}

template<typename T, int max_size>
void stack<T, max_size>::push(T&& value)
{
	if (_size < max_size) {
		_array[_size] = value;
		++_size;
	} else {
		throw std::out_of_range("Stack is full.");
	}
}

template<typename T, int max_size>
template<typename... Args>
void stack<T, max_size>::emplace(Args&& ... args)
{
	if (_size < max_size) {
		_array[_size] = T(std::forward<Args>(args)...);
		++_size;
	} else {
		throw std::out_of_range("Stack is full.");
	}
};

template<typename T, int max_size>
void stack<T, max_size>::pop()
{
	_size = std::max(0UL, --_size);
}

template<typename T, int max_size>
void stack<T, max_size>::swap(stack<T, max_size>& other) noexcept
{
	std::swap(_array, other._array);
	std::swap(_size, other._size);
}

#endif //STACK_H
