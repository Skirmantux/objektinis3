#pragma once

#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <iterator>

template<typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
    // Member types
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = typename std::allocator_traits<Allocator>::size_type;
    using difference_type = typename std::allocator_traits<Allocator>::difference_type;
    using reference = T&;
    using const_reference = const T&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Constructors
    Vector() : _data(nullptr), _size(0), _capacity(0), _alloc(Allocator()) {}

    explicit Vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
        : _size(count), _capacity(count), _alloc(alloc) {
        _data = _alloc.allocate(_capacity);
        std::uninitialized_fill_n(_data, _size, value);
    }

    Vector(const Vector& other) : _size(other._size), _capacity(other._capacity), _alloc(other._alloc) {
        _data = _alloc.allocate(_capacity);
        std::uninitialized_copy_n(other._data, _size, _data);
    }

    Vector(Vector&& other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity), _alloc(std::move(other._alloc)) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator())
        : _size(init.size()), _capacity(init.size()), _alloc(alloc) {
        _data = _alloc.allocate(_capacity);
        std::uninitialized_copy(init.begin(), init.end(), _data);
    }

    ~Vector() {
        clear();
        _alloc.deallocate(_data, _capacity);
    }

    // Assignment operators
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            clear();
            _alloc.deallocate(_data, _capacity);

            _size = other._size;
            _capacity = other._capacity;
            _alloc = other._alloc;
            _data = _alloc.allocate(_capacity);
            std::uninitialized_copy_n(other._data, _size, _data);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            clear();
            _alloc.deallocate(_data, _capacity);

            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            _alloc = std::move(other._alloc);

            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // Element access
    reference at(size_type pos) {
        if (pos >= _size) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return _data[pos];
    }

    const_reference at(size_type pos) const {
        if (pos >= _size) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return _data[pos];
    }

    reference operator[](size_type pos) {
        return _data[pos];
    }

    const_reference operator[](size_type pos) const {
        return _data[pos];
    }

    reference front() {
        return _data[0];
    }

    const_reference front() const {
        return _data[0];
    }

    reference back() {
        return _data[_size - 1];
    }

    const_reference back() const {
        return _data[_size - 1];
    }

    pointer data() noexcept {
        return _data;
    }

    const_pointer data() const noexcept {
        return _data;
    }

    // Iterators
    iterator begin() noexcept {
        return _data;
    }

    const_iterator begin() const noexcept {
        return _data;
    }

    const_iterator cbegin() const noexcept {
        return _data;
    }

    iterator end() noexcept {
        return _data + _size;
    }

    const_iterator end() const noexcept {
        return _data + _size;
    }

    const_iterator cend() const noexcept {
        return _data + _size;
    }

    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }

    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }

    // Capacity
    bool empty() const noexcept {
        return _size == 0;
    }

    size_type size() const noexcept {
        return _size;
    }

    size_type max_size() const noexcept {
        return std::allocator_traits<Allocator>::max_size(_alloc);
    }

    void reserve(size_type new_cap) {
        if (new_cap > _capacity) {
            pointer new_data = _alloc.allocate(new_cap);
            std::uninitialized_move(_data, _data + _size, new_data);
            std::destroy(_data, _data + _size);
            _alloc.deallocate(_data, _capacity);
            _data = new_data;
            _capacity = new_cap;
        }
    }

    size_type capacity() const noexcept {
        return _capacity;
    }

    void shrink_to_fit() {
        if (_size < _capacity) {
            pointer new_data = _alloc.allocate(_size);
            std::uninitialized_move(_data, _data + _size, new_data);
            std::destroy(_data, _data + _size);
            _alloc.deallocate(_data, _capacity);
            _data = new_data;
            _capacity = _size;
        }
    }

    // Modifiers
    void clear() noexcept {
        std::destroy(_data, _data + _size);
        _size = 0;
    }

    void push_back(const T& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new(_data + _size) T(value);
        ++_size;
    }

    void push_back(T&& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new(_data + _size) T(std::move(value));
        ++_size;
    }

    void pop_back() {
        if (_size > 0) {
            --_size;
        }
    }

    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new(_data + _size) T(std::forward<Args>(args)...);
        ++_size;
        return _data[_size - 1];
    }

    iterator insert(const_iterator pos, const T& value) {
        difference_type offset = pos - begin();
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        iterator it = begin() + offset;
        if (it != end()) {
            new(it) T(value);
            std::rotate(it, end() - 1, end());
        }
        ++_size;
        return it;
    }

    iterator insert(const_iterator pos, T&& value) {
        difference_type offset = pos - begin();
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        iterator it = begin() + offset;
        if (it != end()) {
            new(it) T(std::move(value));
            std::rotate(it, end() - 1, end());
        }
        ++_size;
        return it;
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        difference_type offset = pos - begin();
        if (_size + count > _capacity) {
            reserve(_capacity + count);
        }
        iterator it = begin() + offset;
        if (it != end()) {
            std::uninitialized_move(it, end(), it + count);
            std::fill(it, it + count, value);
        }
        _size += count;
        return it;
    }

    template <typename InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        difference_type offset = pos - begin();
        size_type count = std::distance(first, last);
        if (_size + count > _capacity) {
            reserve(_capacity + count);
        }
        iterator it = begin() + offset;
        if (it != end()) {
            std::uninitialized_move(it, end(), it + count);
            std::copy(first, last, it);
        }
        _size += count;
        return it;
    }

    iterator erase(const_iterator pos) {
        return erase(pos, pos + 1);
    }

    iterator erase(const_iterator first, const_iterator last) {
        iterator it = const_cast<iterator>(first);
        iterator end_pos = const_cast<iterator>(last);
        std::move(end_pos, end(), it);
        size_type count = std::distance(first, last);
        std::destroy(end() - count, end());
        _size -= count;
        return it;
    }

    void resize(size_type count) {
        if (count > _size) {
            if (count > _capacity) {
                reserve(count);
            }
            for (size_type i = _size; i < count; ++i) {
                new(_data + i) T();
            }
        }
        else if (count < _size) {
            std::destroy(_data + count, _data + _size);
        }
        _size = count;
    }

    void resize(size_type count, const value_type& value) {
        if (count > _size) {
            if (count > _capacity) {
                reserve(count);
            }
            for (size_type i = _size; i < count; ++i) {
                new(_data + i) T(value);
            }
        }
        else if (count < _size) {
            std::destroy(_data + count, _data + _size);
        }
        _size = count;
    }

    void swap(Vector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        std::swap(_alloc, other._alloc);
    }

private:
    pointer _data;
    size_type _size;
    size_type _capacity;
    allocator_type _alloc;
};
// End vector class
void VectorExample();
int sumVector(const Vector<int>& vec);
bool isSorted(const Vector<int>& vec);
void removeDuplicates(Vector<int>& vec);
Vector<int> mergeSortedVectors(const Vector<int>& vec1, const Vector<int>& vec2);
std::pair<int, int> findMaxElement(const Vector<int>& vec);
void VectorUzpildymas();