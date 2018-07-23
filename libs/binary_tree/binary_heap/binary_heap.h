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
            const uint32_t& _count = _data.length;
            std::function<int32_t(Key, Key)> _compare;

            uint32_t heap_size();
            uint32_t left(uint32_t i);
            uint32_t parent(uint32_t i);
            uint32_t right(uint32_t i);

            void build_heap();
            void heapify(uint32_t i);
        public:
            const uint32_t& length = _count;

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

            bool empty() const;
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
    void binary_heap_t<Key, Value>::heapify(uint32_t i) {
        // https://www.youtube.com/watch?v=B7hVxCmfPtM

        if(heap_size() > 1 && i <= ((heap_size() / 2) - 1)) {
            auto& A = _data;

            uint32_t l = left(i);
            uint32_t r = right(i);

            uint32_t max = i;

            bool b1 = l < heap_size();
            bool b2 = r < heap_size();

            if(b1 && b2) {
                max = _compare(A[l]->key, A[r]->key) > 0 ? l : r;
            } else if(b1) {
                max = l;
            } else if(b2) {
                max = r;
            }

            if(max != i && _compare(A[i]->key, A[max]->key) < 0) {
                std::swap(A[i], A[max]);
                heapify(max);
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
    bool binary_heap_t<Key, Value>::empty() const {
        return _count == 0;
    }

    template<class Key, class Value>
    std::pair<Key, Value> binary_heap_t<Key, Value>::extract() {
        std::pair<Key, Value> result = peek();

        std::swap(_data[0], _data[_count - 1]);
        _data.pop(_count - 1);

        heapify(0);

        return result;
    }

    template<class Key, class Value>
    void binary_heap_t<Key, Value>::insert(Key key, Value value) {
        _data.append(new binary_heap_node_t<Key, Value>(key, value));

        uint32_t i = _count - 1;
        uint32_t p;

        while(i > 0 && _compare(_data[i]->key, _data[p = parent(i)]->key) > 0) {
            std::swap(_data[i], _data[p]);
            i = p;
        }
    }

    template<class Key, class Value>
    std::pair<Key, Value> binary_heap_t<Key, Value>::peek() const {
        if(_count == 0) {
            throw "Heap is empty";
        }

        return std::make_pair(_data[0]->key, _data[0]->value);
    }
}

#endif
