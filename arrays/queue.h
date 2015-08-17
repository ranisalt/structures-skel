#ifndef queue_H
#define queue_H

#include <array>
#include <stdexcept>

template<typename T, int max_size>
class queue {
	using size_type = std::size_t;

public:

	// ctor
	queue() = default;

	// access
	T& front();

	const T& front() const;

	T& back();

	const T& back() const;

	// capacity
	bool empty() const noexcept;

	size_type size() const noexcept;

	// mutators
	void push(const T& value);

	void push(T&& value);

	template<typename... Args>
	void emplace(Args&& ... args);

	void pop();

	void swap(queue& other) noexcept;

	friend void swap(queue<T, max_size>& lhs, queue<T, max_size>& rhs) noexcept
	{ lhs.swap(rhs); }

private:
	std::array<T, max_size> _array;
	size_type _size = 0;
};

template<typename T, int max_size>
T& queue<T, max_size>::front()
{
	return _array.front();
}

template<typename T, int max_size>
const T& queue<T, max_size>::front() const
{
	return front();
}

template<typename T, int max_size>
T& queue<T, max_size>::back()
{
	return _array.at(_size - 1);
}

template<typename T, int max_size>
const T& queue<T, max_size>::back() const
{
	return front();
}

template<typename T, int max_size>
bool queue<T, max_size>::empty() const noexcept
{
	return _size == 0;
}

template<typename T, int max_size>
typename queue<T, max_size>::size_type queue<T, max_size>::size() const noexcept
{
	return _size;
}

template<typename T, int max_size>
void queue<T, max_size>::push(const T& value)
{
	if (_size < max_size) {
		_array[_size] = value;
		++_size;
	} else {
		throw std::out_of_range("queue is full.");
	}
}

template<typename T, int max_size>
void queue<T, max_size>::push(T&& value)
{
	if (_size < max_size) {
		_array[_size] = value;
		++_size;
	} else {
		throw std::out_of_range("queue is full.");
	}
}

template<typename T, int max_size>
template<typename... Args>
void queue<T, max_size>::emplace(Args&& ... args)
{
	if (_size < max_size) {
		_array[_size] = T(std::forward<Args>(args)...);
		++_size;
	} else {
		throw std::out_of_range("queue is full.");
	}
};

template<typename T, int max_size>
void queue<T, max_size>::pop()
{
	std::copy(std::next(_array.begin()), _array.end(), _array.begin());
	_size = std::max(0UL, --_size);
}

template<typename T, int max_size>
void queue<T, max_size>::swap(queue<T, max_size>& other) noexcept
{
	std::swap(_array, other._array);
	std::swap(_size, other._size);
}

#endif //queue_H
