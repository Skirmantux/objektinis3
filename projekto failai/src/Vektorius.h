#pragma once

#include <memory>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <iterator>

/**
 * @brief A dynamically resizing array similar to std::vector.
 *
 * @tparam T The type of elements stored in the vector.
 * @tparam Allocator The type of allocator used to manage memory allocation.
 */
template<typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
    // Member types
    using value_type = T; /**< The type of elements stored in the vector. */
    using allocator_type = Allocator; /**< The type of allocator used for memory allocation. */
    using size_type = typename std::allocator_traits<Allocator>::size_type; /**< An unsigned integer type used to represent sizes. */
    using difference_type = typename std::allocator_traits<Allocator>::difference_type; /**< A signed integer type used to represent differences between iterators. */
    using reference = T&; /**< Reference to an element. */
    using const_reference = const T&; /**< Const reference to an element. */
    using pointer = typename std::allocator_traits<Allocator>::pointer; /**< Pointer to an element. */
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer; /**< Const pointer to an element. */
    using iterator = T*; /**< Iterator for traversing the vector. */
    using const_iterator = const T*; /**< Const iterator for traversing the vector. */
    using reverse_iterator = std::reverse_iterator<iterator>; /**< Reverse iterator for traversing the vector in reverse. */
    using const_reverse_iterator = std::reverse_iterator<const_iterator>; /**< Const reverse iterator for traversing the vector in reverse. */

    // Constructors
    /**
     * @brief Constructs an empty vector.
     */
    Vector() : _data(nullptr), _size(0), _capacity(0), _alloc(Allocator()) {}

    /**
     * @brief Constructs the vector with a specified number of elements, each initialized with a given value.
     *
     * @param count The number of elements in the vector.
     * @param value The value to initialize the elements with.
     * @param alloc The allocator used for memory allocation.
     */
    explicit Vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
        : _size(count), _capacity(count), _alloc(alloc) {
        _data = _alloc.allocate(_capacity);
        std::uninitialized_fill_n(_data, _size, value);
    }

    /**
     * @brief Constructs the vector by copying elements from another vector.
     *
     * @param other The vector to copy.
     */
    Vector(const Vector& other) : _size(other._size), _capacity(other._capacity), _alloc(other._alloc) {
        _data = _alloc.allocate(_capacity);
        std::uninitialized_copy_n(other._data, _size, _data);
    }

    /**
     * @brief Constructs the vector by moving elements from another vector.
     *
     * @param other The vector to move from.
     */
    Vector(Vector&& other) noexcept
        : _data(other._data), _size(other._size), _capacity(other._capacity), _alloc(std::move(other._alloc)) {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    /**
     * @brief Constructs the vector with the elements from the initializer list.
     *
     * @param init The initializer list to initialize the elements of the vector.
     * @param alloc The allocator used for memory allocation.
     */
    Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator())
        : _size(init.size()), _capacity(init.size()), _alloc(alloc) {
        _data = _alloc.allocate(_capacity);
        std::uninitialized_copy(init.begin(), init.end(), _data);
    }

    /**
     * @brief Destroys the vector and deallocates its memory.
     */
    ~Vector() {
        clear();
        _alloc.deallocate(_data, _capacity);
    }

    // Assignment operators
    /**
     * @brief Assigns the contents of another vector to this vector.
     *
     * @param other The vector to copy.
     * @return A reference to this vector after the assignment.
     */
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

    /**
     * @brief Assigns the contents of another vector to this vector by moving.
     *
     * @param other The vector to move from.
     * @return A reference to this vector after the assignment.
     */
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
    /**
     * @brief Accesses the element at the specified position with bounds checking.
     *
     * @param pos The position of the element to access.
     * @return Reference to the element at the specified position.
     * @throw std::out_of_range if pos is out of range.
     */
    reference at(size_type pos) {
        if (pos >= _size) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return _data[pos];
    }

    /**
     * @brief Accesses the element at the specified position with bounds checking.
     *
     * @param pos The position of the element to access.
     * @return Const reference to the element at the specified position.
     * @throw std::out_of_range if pos is out of range.
     */
    const_reference at(size_type pos) const {
        if (pos >= _size) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return _data[pos];
    }

    /**
     * @brief Accesses the element at the specified position without bounds checking.
     *
     * @param pos The position of the element to access.
     * @return Reference to the element at the specified position.
     */
    reference operator[](size_type pos) {
        return _data[pos];
    }

    /**
     * @brief Accesses the element at the specified position without bounds checking.
     *
     * @param pos The position of the element to access.
     * @return Const reference to the element at the specified position.
     */
    const_reference operator[](size_type pos) const {
        return _data[pos];
    }

    /**
     * @brief Accesses the first element in the vector.
     *
     * @return Reference to the first element.
     */
    const_reference front() const {
        return _data[0];
    }

    /**
     * @brief Accesses the last element in the vector.
     *
     * @return Reference to the last element.
     */
    reference back() {
        return _data[_size - 1];
    }

    /**
     * @brief Accesses the last element in the vector.
     *
     * @return Const reference to the last element.
     */
    const_reference back() const {
        return _data[_size - 1];
    }

    /**
     * @brief Returns a pointer to the underlying array serving as element storage.
     *
     * @return Pointer to the underlying element storage.
     */
    pointer data() noexcept {
        return _data;
    }

    /**
     * @brief Returns a const pointer to the underlying array serving as element storage.
     *
     * @return Const pointer to the underlying element storage.
     */
    const_pointer data() const noexcept {
        return _data;
    }

    // Iterators
    /**
     * @brief Returns an iterator to the beginning of the vector.
     *
     * @return Iterator to the beginning of the vector.
     */
    iterator begin() noexcept {
        return _data;
    }

    /**
     * @brief Returns a const iterator to the beginning of the vector.
     *
     * @return Const iterator to the beginning of the vector.
     */
    const_iterator begin() const noexcept {
        return _data;
    }

    /**
     * @brief Returns a const iterator to the beginning of the vector.
     *
     * @return Const iterator to the beginning of the vector.
     */
    const_iterator cbegin() const noexcept {
        return _data;
    }

    /**
     * @brief Returns an iterator to the end of the vector.
     *
     * @return Iterator to the end of the vector.
     */
    iterator end() noexcept {
        return _data + _size;
    }

    /**
     * @brief Returns a const iterator to the end of the vector.
     *
     * @return Const iterator to the end of the vector.
     */
    const_iterator end() const noexcept {
        return _data + _size;
    }

    /**
     * @brief Returns a const iterator to the end of the vector.
     *
     * @return Const iterator to the end of the vector.
     */
    const_iterator cend() const noexcept {
        return _data + _size;
    }

    /**
     * @brief Returns a reverse iterator to the beginning of the reversed vector.
     *
     * @return Reverse iterator to the beginning of the reversed vector.
     */
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }

    /**
     * @brief Returns a const reverse iterator to the beginning of the reversed vector.
     *
     * @return Const reverse iterator to the beginning of the reversed vector.
     */
    const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    /**
     * @brief Returns a reverse iterator to the end of the reversed vector.
     *
     * @return Reverse iterator to the end of the reversed vector.
     */
    reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }

    /**
     * @brief Returns a const reverse iterator to the end of the reversed vector.
     *
     * @return Const reverse iterator to the end of the reversed vector.
     */
    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }

    /**
     * @brief Returns a const reverse iterator to the beginning of the reversed vector.
     *
     * @return Const reverse iterator to the beginning of the reversed vector.
     */
    const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }

    /**
     * @brief Returns a const reverse iterator to the end of the reversed vector.
     *
     * @return Const reverse iterator to the end of the reversed vector.
     */
    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }

    // Capacity
    /**
     * @brief Checks if the vector is empty.
     *
     * @return True if the vector is empty, false otherwise.
     */
    bool empty() const noexcept {
        return _size == 0;
    }

    /**
     * @brief Returns the number of elements in the vector.
     *
     * @return The number of elements in the vector.
     */
    size_type size() const noexcept {
        return _size;
    }

    /**
     * @brief Returns the maximum number of elements the vector can hold.
     *
     * @return The maximum number of elements the vector can hold.
     */
    size_type max_size() const noexcept {
        return std::allocator_traits<Allocator>::max_size(_alloc);
    }

    /**
     * @brief Increases the capacity of the vector to a value greater than or equal to new_cap.
     *
     * @param new_cap The new capacity of the vector.
     */
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

    /**
     * @brief Returns the current capacity of the vector.
     *
     * @return The current capacity of the vector.
     */
    size_type capacity() const noexcept {
        return _capacity;
    }

    /**
     * @brief Reduces the capacity of the vector to fit its size.
     */
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
    /**
     * @brief Clears the contents of the vector.
     */
    void clear() noexcept {
        std::destroy(_data, _data + _size);
        _size = 0;
    }

    /**
     * @brief Adds an element to the end of the vector.
     *
     * @param value The value to be added to the vector.
     */
    void push_back(const T& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new(_data + _size) T(value);
        ++_size;
    }

    /**
     * @brief Moves an element to the end of the vector.
     *
     * @param value The value to be moved to the vector.
     */
    void push_back(T&& value) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new(_data + _size) T(std::move(value));
        ++_size;
    }

    /**
     * @brief Removes the last element from the vector.
     */
    void pop_back() {
        if (_size > 0) {
            --_size;
        }
    }

    /**
     * @brief Constructs an element in-place at the end of the vector.
     *
     * @tparam Args Types of arguments to forward to the constructor of the element.
     * @param args Arguments to forward to the constructor of the element.
     * @return Reference to the newly constructed element.
     */
    template <typename... Args>
    reference emplace_back(Args&&... args) {
        if (_size == _capacity) {
            reserve(_capacity == 0 ? 1 : _capacity * 2);
        }
        new(_data + _size) T(std::forward<Args>(args)...);
        ++_size;
        return _data[_size - 1];
    }

    /**
     * @brief Inserts an element into the vector at the specified position.
     *
     * @param pos Iterator pointing to the position where the element should be inserted.
     * @param value The value to be inserted.
     * @return Iterator pointing to the inserted element.
     */
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

    /**
     * @brief Inserts an element into the vector at the specified position by moving.
     *
     * @param pos Iterator pointing to the position where the element should be inserted.
     * @param value The value to be moved into the vector.
     * @return Iterator pointing to the inserted element.
     */
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

    /**
     * @brief Inserts multiple elements into the vector at the specified position.
     *
     * @param pos Iterator pointing to the position where the elements should be inserted.
     * @param count The number of elements to insert.
     * @param value The value to initialize the inserted elements with.
     * @return Iterator pointing to the first inserted element.
     */
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

    /**
     * @brief Inserts elements from a range into the vector at the specified position.
     *
     * @tparam InputIt Type of the input iterator.
     * @param pos Iterator pointing to the position where the elements should be inserted.
     * @param first Iterator to the beginning of the range.
     * @param last Iterator to the end of the range.
     * @return Iterator pointing to the first inserted element.
     */
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

    /**
     * @brief Erases an element from the vector at the specified position.
     *
     * @param pos Iterator pointing to the element to be erased.
     * @return Iterator following the last removed element.
     */
    iterator erase(const_iterator pos) {
        return erase(pos, pos + 1);
    }

    /**
     * @brief Erases elements in the range [first, last) from the vector.
     *
     * @param first Iterator to the beginning of the range to be erased.
     * @param last Iterator to the end of the range to be erased.
     * @return Iterator following the last removed element.
     */
    iterator erase(const_iterator first, const_iterator last) {
        iterator it = const_cast<iterator>(first);
        iterator end_pos = const_cast<iterator>(last);
        std::move(end_pos, end(), it);
        size_type count = std::distance(first, last);
        std::destroy(end() - count, end());
        _size -= count;
        return it;
    }

    /**
     * @brief Resizes the vector to contain the specified number of elements.
     *
     * If the current size is greater than the count, elements are destroyed.
     * If the current size is less than the count, additional elements are default-constructed.
     *
     * @param count The new size of the vector.
     */
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

    /**
     * @brief Resizes the vector to contain the specified number of elements.
     *
     * If the current size is greater than the count, elements are destroyed.
     * If the current size is less than the count, additional elements are value-initialized with value.
     *
     * @param count The new size of the vector.
     * @param value The value to initialize the new elements with.
     */
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

    /**
     * @brief Swaps the contents of this vector with another vector.
     *
     * @param other The vector to swap with.
     */
    void swap(Vector& other) noexcept {
        swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        std::swap(_alloc, other._alloc);
    }
private:
     T* _data; /**< Pointer to the underlying data array. */
     size_type _size; /**< The number of elements in the vector. */
     size_type _capacity; /**< The number of elements that can be held in currently allocated storage. */
     Allocator _alloc; /**< The allocator instance used to allocate and deallocate memory. */
};

/**
 * @brief Example function demonstrating the usage of the Vector class.
 */
void VectorExample();

/**
 * @brief Sums the elements of the given vector.
 *
 * @param vec The vector whose elements are to be summed.
 * @return The sum of the elements.
 */
int sumVector(const Vector<int>& vec);

/**
 * @brief Checks if the given vector is sorted in ascending order.
 *
 * @param vec The vector to be checked.
 * @return True if the vector is sorted, false otherwise.
 */
bool isSorted(const Vector<int>& vec);

/**
 * @brief Removes duplicate elements from the given vector.
 *
 * @param vec The vector from which duplicate elements are to be removed.
 */
void removeDuplicates(Vector<int>& vec);

/**
 * @brief Merges two sorted vectors into a single sorted vector.
 *
 * @param vec1 The first sorted vector.
 * @param vec2 The second sorted vector.
 * @return A new vector containing all elements from both input vectors, sorted in ascending order.
 */
Vector<int> mergeSortedVectors(const Vector<int>& vec1, const Vector<int>& vec2);

/**
 * @brief Finds the maximum element and its index in the given vector.
 *
 * @param vec The vector in which to search for the maximum element.
 * @return A pair containing the maximum element and its index.
 */
std::pair<int, int> findMaxElement(const Vector<int>& vec);

/**
 * @brief Example function demonstrating the usage of filling the vector with data.
 */
void VectorUzpildymas();