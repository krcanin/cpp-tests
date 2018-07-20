#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "binary_heap_node.h"
#include "../../list/list.h"

namespace crap {
    // -----------
    // NOTES
    // -----------
    // - standard comparison function results in min-heap

    template<class Key, class Value>
    class binary_heap_t {
        public:
            list_t<binary_heap_node_t<Key, Value>*> _data;
            uint32_t _count = 0;
            std::function<int32_t(Key, Key)> _compare;

            uint32_t heap_size();
            uint32_t left(uint32_t i);
            uint32_t parent(uint32_t i);
            uint32_t right(uint32_t i);

            void build_heap();
            void heapify(uint32_t i);
        public:
            uint32_t& length = _count;

            // -----------
            // MANDATORY
            // -----------

            binary_heap_t(const binary_heap_t<Key, Value>& rhs);
            binary_heap_t(binary_heap_t<Key, Value>&& rhs);

            ~binary_heap_t();

            binary_heap_t<Key, Value>& operator=(const binary_heap_t<Key, Value>& rhs);
            binary_heap_t<Key, Value>& operator=(binary_heap_t<Key, Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            binary_heap_t(std::function<int32_t(Key, Key)> compare = [](Key x, Key y) { return x - y; });

            std::pair<Key, Value> extract();
            void insert(Key key, Value value);
            std::pair<Key, Value> peek() const;
    };

    // -----------
    // PRIVATE
    // -----------

    template<class Key, class Value>
    uint32_t binary_heap_t<Key, Value>::heap_size() {
        return _count;
    }

    template<class Key, class Value>
    uint32_t binary_heap_t<Key, Value>::left(uint32_t i) {
        return (2 * i) + 1;
    }

    template<class Key, class Value>
    uint32_t binary_heap_t<Key, Value>::parent(uint32_t i) {
        return (i - 1) / 2;
    }

    template<class Key, class Value>
    uint32_t binary_heap_t<Key, Value>::right(uint32_t i) {
        return (2 * i) + 2;
    }

    template<class Key, class Value>
    void binary_heap_t<Key, Value>::build_heap() {
        for(uint32_t i = (_count / 2) - 1; i >= 0; i -= 1) {
            heapify(i);
        }
    }

    template<class Key, class Value>
    void binary_heap_t<Key, Value>::heapify(uint32_t i) {
        // https://www.youtube.com/watch?v=B7hVxCmfPtM

        if(i < (heap_size() / 2)) {
            auto& A = _data;

            if(A[i] < A[left(i)]) {
                std::swap(A[i], A[left(i)]);
                heapify(left(i));
            } else if(A[i] < A[right(i)]) {
                std::swap(A[i], A[right(i)]);
                heapify(right(i));
            }
        }
    }

    // -----------
    // MANDATORY
    // -----------

    template<class Key, class Value>
    binary_heap_t<Key, Value>::binary_heap_t(const binary_heap_t<Key, Value>& rhs) : _data(rhs._data) {
        _count = rhs._count;
        _compare = rhs._compare;
    }

    template<class Key, class Value>
    binary_heap_t<Key, Value>::binary_heap_t(binary_heap_t<Key, Value>&& rhs) : _data(std::move(rhs._data)) {
        _count = rhs._count;
        rhs._count = 0;

        _compare = rhs._compare;
        rhs._compare = nullptr;
    }

    template<class Key, class Value>
    binary_heap_t<Key, Value>::~binary_heap_t() {
        for(uint32_t i = 0; i < _data.length; i += 1) {
            delete _data[i];
        }
    }

    template<class Key, class Value>
    binary_heap_t<Key, Value>& binary_heap_t<Key, Value>::operator=(const binary_heap_t<Key, Value>& rhs) {
        _data = list_t<binary_heap_node_t<Key, Value>*>(rhs._data);
        _count = rhs._count;
        _compare = rhs._compare;
    }

    template<class Key, class Value>
    binary_heap_t<Key, Value>& binary_heap_t<Key, Value>::operator=(binary_heap_t<Key, Value>&& rhs) {
        _data = list_t<binary_heap_node_t<Key, Value>*>(std::move(rhs._data));

        _count = rhs._count;
        rhs._count = 0;

        _compare = rhs._compare;
        rhs._compare = nullptr;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Key, class Value>
    binary_heap_t<Key, Value>::binary_heap_t(std::function<int32_t(Key, Key)> compare) : _compare(compare) {}

    template<class Key, class Value>
    std::pair<Key, Value> binary_heap_t<Key, Value>::extract() {
        std::pair<Key, Value> result = peek();
        _data.pop(0);
        _count -= 1;
        build_heap();
    }

    template<class Key, class Value>
    void binary_heap_t<Key, Value>::insert(Key key, Value value) {
        _data.append(new binary_heap_node_t<Key, Value>(key, value));
		_count += 1;

        list_t<binary_heap_node_t<Key, Value>*>& A = _data;
        uint32_t i = parent(heap_size() - 1);

        while(i >= 0 && A[i] > A[parent(i)]) {
            std::swap(A[i], A[parent(i)]);
            i = parent(i);
        }
    }

    template<class Key, class Value>
    std::pair<Key, Value> binary_heap_t<Key, Value>::peek() const {
        return std::make_pair(_data[0]->key, _data[0]->value);
    }
}

#endif
