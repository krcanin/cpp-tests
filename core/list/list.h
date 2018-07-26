#ifndef LIST_H
#define LIST_H

#include <cstdint>
#include <initializer_list>
#include <utility>
#include <functional>
#include <algorithm>

#include "list_iterator.h"
#include "list_reverse_iterator.h"

namespace mylib {
    template<typename Value>
    class list_t {
        // -----------
        // NOTES
        // -----------
        // - Value requires copy constructor
        // - copy(Value), insert(uint32_t, Value) and index(Value, uint32_t, uint32_t) requires overloaded equals-operator
        // - if you are working with an iterator, do not modify the list while iterating because of UB :)
        // - start & end indices are always meant to be in the interval [start; end[ which means that start is inclusive and end is exclusive
        // - if no comparison function is given at the sorting-related methods, cmp(x, y) = x - y is expected
        //   and if no key function is given, key(x) = x is expected

        private:
            Value** _elements = nullptr;
            uint32_t _size = 0, _count = 0;
            const uint32_t _initial_size = 0;

            void append(Value* item);

            template<class U> void insertion_sort(uint32_t left, uint32_t right, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse);

            template<class U> void merge(uint32_t left, uint32_t middle, uint32_t right, std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key, bool reverse);

            void resize(uint32_t n);
        public:
            const uint32_t& length = _count;
            const uint32_t& capacity = _size;

            // -----------
            // MANDATORY
            // -----------

            list_t();
            list_t(const list_t<Value>& rhs);
            list_t(list_t<Value>&& rhs);

            virtual ~list_t();

            list_t<Value>& operator=(const list_t<Value>& rhs);
            list_t<Value>& operator=(list_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            explicit list_t(uint32_t initial_size);
            list_t(std::initializer_list<Value> rhs);

            void append(Value item);
            template<class... Args> void append(Value item, Args... rest);

            list_iterator_t<Value> begin() const;

            void clear();

            list_t<Value>* copy() const;

            uint32_t count(Value item) const;

            list_iterator_t<Value> end() const;

            template<class Iter> void extend(Iter it);
            void extend(std::initializer_list<Value> elements);
            void extend(Value* arr, uint32_t l, uint32_t r);
            void extend(Value* arr, uint32_t n);

            uint32_t index(Value item, uint32_t start, uint32_t end) const;
            uint32_t index(Value item, uint32_t start) const;
            uint32_t index(Value item) const;

            void insert(uint32_t index, Value item);

            template<class U> bool is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) const;
            template<class U> bool is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key) const;
            bool is_sorted(std::function<int32_t(Value, Value)> cmp) const;
            bool is_sorted() const;

            Value pop(uint32_t index);
            Value pop();

            list_reverse_iterator_t<Value> rbegin() const;

            void remove(Value item);

            list_reverse_iterator_t<Value> rend() const;

            void reverse();

            // stable & in-place ~> Timsort
            template<class U> void sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key, bool reverse);
            template<class U> void sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key);
            void sort(std::function<int32_t(Value, Value)> cmp);
            void sort();

            list_t<Value>* sublist(uint32_t left, uint32_t right, uint32_t step) const;

            Value& operator[](uint32_t index) const;

            template<class Iter> list_t<Value>* operator+(Iter rhs) const;
            list_t<Value>* operator+(const list_t<Value>& rhs) const;

            template<class Iter> list_t<Value>& operator+=(Iter rhs);
            list_t<Value>& operator+=(const list_t<Value>& rhs);

            list_t<Value>* operator*(uint32_t amount) const;
    };

    // -----------
    // PRIVATE
    // -----------

    template<typename Value>
    void list_t<Value>::append(Value* item) {
        _elements[_count++] = item;

        if(_count == _size) {
            resize(_size * 2);
        }
    }

    template<typename Value>
    template<class U>
    void list_t<Value>::insertion_sort(uint32_t left, uint32_t right, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) {
        uint32_t j;

        for (uint32_t i = left + 1; i < right; i += 1) {
            j = i;

            while (j > left) {
                int cmp_r = cmp(key(*_elements[j]), key(*_elements[j - 1]));
                cmp_r = reverse ? -cmp_r : cmp_r;

                if(cmp_r < 0) {
                    std::swap(_elements[j], _elements[j - 1]);
                    j -= 1;
                } else {
                    break;
                }
            }
        }
    }

    template<typename Value>
    template<class U>
    void list_t<Value>::merge(uint32_t left, uint32_t middle, uint32_t right, std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key, bool reverse) {
        uint32_t n1 = middle - left;
        uint32_t n2 = right - middle;

        // divide!
        Value** left_part = new Value*[n1];
        Value** right_part = new Value*[n2];

        for (uint32_t i = 0; i < n1; i += 1) {
            left_part[i] = _elements[i + left];
        }

        for (uint32_t i = 0; i < n2; i += 1) {
            right_part[i] = _elements[i + middle];
        }

        // conquer!
        uint32_t i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            int cmp_r = cmp(key(*left_part[i]), key(*right_part[j]));
            cmp_r = reverse ? -cmp_r : cmp_r;

            if (cmp_r < 0) {
                _elements[k++] = left_part[i++];
            } else {
                _elements[k++] = right_part[j++];
            }
        }

        while (i < n1) {
            _elements[k++] = left_part[i++];
        }

        while (j < n2) {
            _elements[k++] = right_part[j++];
        }

        // collect garbage...
        delete[] left_part;
        delete[] right_part;
    }

    template<typename Value>
    void list_t<Value>::resize(uint32_t n) {
        if(n > _size) {
            Value** copy = new Value*[n];

            // copy previous elements into copy
            for (uint32_t i = 0; i < _size; i += 1) {
                copy[i] = _elements[i];
            }

            // fill up with 0's
            for (uint32_t i = _size + 1, end = n; i < end; i += 1) {
                copy[i] = nullptr;
            }

            _size = n;

            // overwrite elements pointer
            delete[] _elements;
            _elements = copy;
        } else {
            throw "Invalid resize value";
        }
    }

    // -----------
    // MANDATORY
    // -----------

    template<typename Value>
    list_t<Value>::list_t() : list_t(128) {}

    template<typename Value>
    list_t<Value>::list_t(const list_t<Value>& rhs) : list_t(rhs._initial_size) {
        for(Value item : rhs) {
            append(item);
        }
    }

    template<typename Value>
    list_t<Value>::list_t(list_t<Value>&& rhs) {
        _elements = rhs._elements;
        _size = rhs._size;
        _count = rhs._count;
        _initial_size = rhs._initial_size;

        rhs._elements = nullptr;
        rhs._size = 0;
        rhs._count = 0;
    }

    template<typename Value>
    list_t<Value>::~list_t() {
        for (uint32_t i = 0; i < _count; i += 1) {
            delete _elements[i];
        }

        delete[] _elements;
    }

    template<typename Value>
    list_t<Value>& list_t<Value>::operator=(const list_t<Value>& rhs) {
        clear();

        for(Value item : rhs) {
            append(item);
        }
    }

    template<typename Value>
    list_t<Value>& list_t<Value>::operator=(list_t<Value>&& rhs) {
        clear();

        _elements = rhs._elements;
        _size = rhs._size;
        _count = rhs._count;

        rhs._elements = nullptr;
        rhs._size = 0;
        rhs._count = 0;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<typename Value>
    list_t<Value>::list_t(uint32_t initial_size) : _initial_size(initial_size) {
        if (initial_size == 0) {
            throw "Initial size must be > 0";
        }

        _elements = new Value*[initial_size]();

        if (_elements == nullptr) {
            throw "Not enough memory left";
        }

        _size = initial_size;
        _count = 0;
    }

    template<typename Value>
    list_t<Value>::list_t(std::initializer_list<Value> rhs) : list_t(128) {
        for(Value item : rhs) {
            append(item);
        }
    }

    template<typename Value>
    void list_t<Value>::append(Value item) {
        append(new Value(item));
    }

    template<typename Value>
    template<class... Args>
    void list_t<Value>::append(Value item, Args... rest) {
        append(item);
        append(rest...);
    }

    template<typename Value>
    list_iterator_t<Value> list_t<Value>::begin() const {
        return list_iterator_t<Value>(_elements, 0, _count);
    }

    template<typename Value>
    void list_t<Value>::clear() {
        this->~list_t();
        _elements = new Value*[_size = _initial_size]();
        _count = 0;
    }

    template<typename Value>
    list_t<Value>* list_t<Value>::copy() const {
        return new list_t<Value>(*this);
    }

    template<typename Value>
    uint32_t list_t<Value>::count(Value item) const {
        uint32_t result = 0;

        for (uint32_t i = 0; i < _count; i += 1) {
            if (*_elements[i] == item) {
                result += 1;
            }
        }

        return result;
    }

    template<typename Value>
    list_iterator_t<Value> list_t<Value>::end() const {
        return list_iterator_t<Value>(nullptr, _count, _count);
    }

    template<typename Value>
    template<class Iter>
    void list_t<Value>::extend(Iter rhs) {
        for(Value item : rhs) {
            append(item);
        }
    }

    template<typename Value>
    void list_t<Value>::extend(std::initializer_list<Value> elements) {
        for (Value item : elements) {
            append(item);
        }
    }

    template<typename Value>
    void list_t<Value>::extend(Value* arr, uint32_t l, uint32_t r) {
        for (uint32_t i = l; i < r; i += 1) {
            append(arr[i]);
        }
    }

    template<typename Value>
    void list_t<Value>::extend(Value* arr, uint32_t n) {
        extend(arr, 0, n);
    }

    template<typename Value>
    uint32_t list_t<Value>::index(Value item, uint32_t start, uint32_t end) const {
        if (start >= _count) {
            throw "Start index out of range";
        }

        if (end > _count) {
            throw "End index out of range";
        }

        for (uint32_t i = start; i < end; i += 1) {
            if (*_elements[i] == item) {
                return i;
            }
        }

        throw "Item not found";
    }

    template<typename Value>
    uint32_t list_t<Value>::index(Value item, uint32_t start) const {
        return index(item, start, _count);
    }

    template<typename Value>
    uint32_t list_t<Value>::index(Value item) const {
        return index(item, 0, _count);
    }

    template<typename Value>
    void list_t<Value>::insert(uint32_t index, Value item) {
        if (index > _count) {
            throw "Index out of range";
        }

        // use append(Value) to ensure that enough space is present
        append(*_elements[_count - 1]);

        // move everything one further up in ]index, _count - 2]
        for (uint32_t i = _count - 2, end = index; i > end; i -= 1) {
            _elements[i] = _elements[i - 1];
        }

        // insert new stuff
        _elements[index] = new Value(item);
    }

    template<typename Value>
    template<class U>
    bool list_t<Value>::is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) const {
        if(_count <= 1) {
            return true;
        } else {
            auto it = begin();
            Value current = *it;
            it += 1;

            while(it != end()) {
                int cmp_r = cmp(key(*it), key(current));
                cmp_r = reverse ? -cmp_r : cmp_r;

                if (cmp_r < 0) {
                    return false;
                }

                current = *it;
                it += 1;
            }
        }
    }

    template<typename Value>
    template<class U>
    bool list_t<Value>::is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key) const {
        return is_sorted(cmp, key, false);
    }

    template<typename Value>
    bool list_t<Value>::is_sorted(std::function<int32_t(Value, Value)> cmp) const {
        return is_sorted<Value>(cmp, [](Value x) { return x; }, false);
    }

    template<typename Value>
    bool list_t<Value>::is_sorted() const {
        return is_sorted<Value>([](Value x, Value y) { return x - y; }, [](Value x) { return x; }, false);
    }

    template<typename Value>
    Value list_t<Value>::pop(uint32_t index) {
        if (index >= _count) {
            throw "Index out of range";
        }

        Value result = *_elements[index];
        delete _elements[index];

        for (uint32_t i = index, end = _count - 1; i < end; i += 1) {
            _elements[i] = _elements[i + 1];
        }

        _elements[_count -= 1] = nullptr;

        return result;
    }

    template<typename Value>
    Value list_t<Value>::pop() {
        return pop(_count - 1);
    }

    template<typename Value>
    list_reverse_iterator_t<Value> list_t<Value>::rbegin() const {
        return list_reverse_iterator_t<Value>(_elements, _count - 1, _count);
    }

    template<typename Value>
    void list_t<Value>::remove(Value item) {
        pop(index(item));
    }

    template<typename Value>
    list_reverse_iterator_t<Value> list_t<Value>::rend() const {
        return list_reverse_iterator_t<Value>(nullptr, 0, _count);
    }

    template<typename Value>
    void list_t<Value>::reverse() {
        for (uint32_t i = 0, end = _count / 2; i < end; i += 1) {
            std::swap(_elements[i], _elements[_count - i - 1]);
        }
    }

    template<typename Value>
    template<class U>
    void list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key, bool reverse) {
        // inspired by https://www.geeksforgeeks.org/timsort/
        const uint32_t RUN_SIZE = 32;

        // divide! (pre-sort the given parts of size RUN_SIZE with insertion sort)
        for (uint32_t i = 0; i < _count; i += RUN_SIZE) {
            insertion_sort(i, std::min(i + RUN_SIZE, _count), cmp, key, reverse);
        }

        // conquer!
        for (uint32_t size = RUN_SIZE; size < _count; size <<= 1) {
            for (uint32_t i = 0; i < _count; i += size << 1) {
                uint32_t left = i;
                uint32_t middle = i + size;
                uint32_t right = std::min<uint32_t>(i + (size << 1), _count);

                merge(left, middle, right, cmp, key, reverse);
            }
        }

        /*
         * example:
         *
         * merge(0, 32, 64)     \
         * merge(64, 96, 128)    |- size = 32
         * merge(128, 160, 196)  |- i = [0, 64, 128, 196]
         * merge(196, 224, 256) /
         *
         * merge(0, 64, 128)     \- size = 64
         * merge(128, 196, 256)  /- i = [0, 128]
         *
         * merge(0, 128, 256)     - size = 128, i = [0]
         */
    }

    template<typename Value>
    template<class U>
    void list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key) {
        sort(cmp, key, false);
    }

    template<typename Value>
    void list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp) {
        sort<Value>(cmp, [](Value x) { return x; }, false);
    }

    template<typename Value>
    void list_t<Value>::sort() {
        sort<Value>([](Value x, Value y) { return x - y; }, [](Value x) { return x; }, false);
    }

    template<typename Value>
    list_t<Value>* list_t<Value>::sublist(uint32_t left, uint32_t right, uint32_t step) const {
        if (right >= _count) {
            throw "End index out of range";
        }

        if (step == 0) {
            throw "Invalid step size";
        }

        list_t<Value>* result = new list_t<Value>();

        for (uint32_t i = left; i < right; i += step) {
            result->append(*_elements[i]);
        }

        return result;
    }

    template<typename Value>
    Value& list_t<Value>::operator[](uint32_t index) const {
        return *_elements[index];
    }

    template<typename Value>
    template<class Iter>
    list_t<Value>* list_t<Value>::operator+(Iter rhs) const {
        list_t<Value>* result = new list_t<Value>(*this);

        for(Value item : rhs) {
            result->append(item);
        }

        return result;
    }

    template<typename Value>
    list_t<Value>* list_t<Value>::operator+(const list_t<Value>& rhs) const {
        list_t<Value>* result = new list_t<Value>(*this);

        for(Value item : rhs) {
            result->append(item);
        }

        return result;
    }

    template<typename Value>
    template<class Iter>
    list_t<Value>& list_t<Value>::operator+=(Iter rhs) {
        return operator=(operator+(rhs));
    }

    template<typename Value>
    list_t<Value>& list_t<Value>::operator+=(const list_t<Value>& rhs) {
        return operator=(operator+(rhs));
    }

    template<typename Value>
    list_t<Value>* list_t<Value>::operator*(uint32_t amount) const {
        if(amount == 0) {
            return new list_t<Value>();
        } else {
            list_t<Value>* result = new list_t<Value>(_count * amount);

            for(uint32_t i = 0; i < amount; i += 1) {
                for(uint32_t j = 0; j < _count; j += 1) {
                    result->append(*_elements[j]);
                }
            }

            return result;
        }
    }
}

#endif
