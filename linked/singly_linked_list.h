#ifndef SINGLY_LINKED_LIST_H_
#define SINGLY_LINKED_LIST_H_

#include <algorithm>
#include <stdexcept>
#include "abstract/list.h"

template<typename T>
class singly_linked_list: public list<T> {
private:
    struct node {
        node(node* succ, T item): succ{succ}, item{std::move(item)} {}

        node* succ;
        T item;
    };

    template<typename NodeT>
    class iterator_base {
    public:
        iterator_base(node* ptr): ptr{ptr} {}

        iterator_base operator=(const iterator_base& other) {
            return {other.ptr};
        }

        iterator_base& operator++() {
            if (!ptr)
                throw std::out_of_range("Iterating beyond list end.");
            ptr = ptr->succ;
            return *this;
        }

        iterator_base operator++(int) {
            node* old = ptr;
            ++(*this);
            return {old};
        }

        bool operator==(const iterator_base& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator_base& other) const {
            return ptr != other.ptr;
        }

        NodeT& operator*() const {
            return ptr->item;
        }

        NodeT* operator->() const {
            return &(ptr->item);
        }

    private:
        node* ptr;
    };

    using parent = list<T>;
    using self = singly_linked_list<T>;
    using size_type = std::size_t;

public:
    singly_linked_list() = default;

    singly_linked_list(const self& other) {
        for (auto e : other)
            push_back(e);
    }

    ~singly_linked_list() {
        node* old;
        while (head) {
            old = head;
            head = head->succ;
            delete old;
        }
    }

    T at(size_type position) const {
        if (position >= _size)
            throw std::out_of_range("Out of range access.");

        node* p = head;
        for (size_type i = 0; i < position; ++i)
            p = p->succ;
        return p->item;
    }

    T back() const {
        empty_check();

        node* p = head;
        while (p->succ != 0)
            p = p->succ;
        return p->item;
    }

    T front() const {
        empty_check();

        return head->item;
    }

    size_type size() const {
        return _size;
    }

    /**< Removal operations */
    T pop(size_type position) {
        if (position >= _size)
            throw std::out_of_range("Empty list.");

        if (position == 0)
            return pop_front();

        node* p = head;
        for (size_type i = 1; i < position; ++i)
            p = p->succ;

        /**< Hold node, advance it and then delete the old one */
        node* aux = p->succ;
        T value{std::move(aux->item)};
        p->succ = aux->succ;
        delete aux;

        --_size;
        return value;
    }

    T pop_back() {
        return pop(_size - 1);
    }

    T pop_front() {
        empty_check();

        /**< Hold head, advance it and then delete the old one */
        node* aux = head;
        T value{std::move(aux->item)};
        head = aux->succ;
        delete aux;

        --_size;
        return value;
    }

    /**< Insertion operations */
    void push(size_type position, const T& item) {
        if (position > _size)
            throw std::out_of_range("Out of range access.");

        if (position == 0) {
            push_front(item);
            return;
        }

        node* p = head;
        for (size_type i = 1; i < position; ++i)
            p = p->succ;
        p->succ = new node(p->succ, item);
        ++_size;
    }

    void push_back(const T& value) {
        push(_size, value);
    }

    void push_front(const T& value) {
        head = new node(head, value);
        ++_size;
    }

    using iterator = iterator_base<T>;

    iterator begin() {
        return {head};
    }

    iterator end() {
        return {nullptr};
    }

    using const_iterator = iterator_base<const T>;

    const_iterator begin() const {
        return {head};
    }

    const_iterator end() const {
        return {nullptr};
    }

    self& operator=(self&& rhs) {
        swap(*this, rhs);
        return *this;
    }

    bool operator==(const self& rhs) const {
        if (_size == rhs._size) {
            for (const_iterator a = begin(), b = rhs.begin();
                    a != end() && b != rhs.end(); ++a, ++b)
                if (*a != *b)
                    return false;
            return true;
        }
        return false;
    }

    bool operator!=(const self& rhs) const {
        return not (*this == rhs);
    }

    friend void swap(self& a, self& b) {
        using std::swap;

        swap(a.head, b.head);
        swap(a._size, b._size);
    }

private:
    void empty_check() const {
        if (!_size)
            throw std::out_of_range("Empty list.");
    }

    node* head{nullptr};
    size_type _size{0u};
};

#endif /* SINGLY_LINKED_LIST_H_ */
