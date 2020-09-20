#ifndef LIST_H_
#define LIST_H_

template<typename T>
class list {
protected:
	template<typename NodeT>
	class iterator_base;

	using size_type = std::size_t;

public:
	virtual ~list() {};

	virtual T at(size_type) const = 0;
	virtual T back() const = 0;
	virtual T front() const = 0;

	virtual size_type size() const = 0;

	/**< Removal operations */
	virtual T pop(size_type) = 0;
	virtual T pop_back() = 0;
	virtual T pop_front() = 0;

	/**< Insertion operations */
	virtual void push(size_type, const T&) = 0;
	virtual void push_back(const T&) = 0;
	virtual void push_front(const T&) = 0;

	/**< Mutable iterator definition */
	using iterator = iterator_base<T>;
	iterator begin();
	iterator end();

	/**< Constant iterator definition */
	using const_iterator = iterator_base<const T>;
	const_iterator begin() const;
	const_iterator end() const;
};

#endif /* LIST_H_ */
