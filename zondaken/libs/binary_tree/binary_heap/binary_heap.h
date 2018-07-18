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
        private:
            list_t<binary_heap_node<Key, Value>*> _data;
            uint32_t _count = 0;
            std::function<int32_t(Key, Key)> _compare;

            void build_max_heap();
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

            binary_heap_t(std::function<Key, Value> compare = [](Key x, Key y) { return x - y; });

            std::pair<Key, Value> extract();
            void insert(Key key, Value value);
            std::pair<Key, Value> peek() const;
    };

    // -----------
    // PRIVATE
    // -----------

    template<class Key, class Value>
    void binary_heap_t<Key, Value>::build_heap() {
        uint32_t i = (_count / 2) - 1;

        bool flag = true;

        while (i >= 0 && flag) {
            heapify(i);

            if (i == 0) {
                flag = false;
            } else {
                i -= 1;
            }
        }
    }

    template<class Key, class Value>
    void binary_heap_t<Key, Value>::heapify(uint32_t i) {
    	uint32_t n = _length;

    	uint32_t l = 2 * i + 1;
    	uint32_t r = l + 1;

    	if(i < n) {
    		uint32_t max = 0;
    		bool flag = false;

    		if(l < n && r < n) {
    			max = _compare(_data[l]->key, _data[r]->key) < 0 ? l : r;
    			flag = true;
    		} else if(l < n) {
    			max = l;
    			flag = true;
    		} else if(r < n) {
    			max = r;
    			flag = true;
    		}

    		if(flag && _compare(_data[max]->key, _data[i]->key) < 0) {
    			std::swap(_data[i], _data[max]);
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
    binary_heap_t<Key, Value>::binary_heap_t(std::function<Key, Value> compare) : _compare(compare) {}

    template<class Key, class Value>
    std::pair<Key, Value> binary_heap_t<Key, Value>::extract() {
        std::pair<Key, Value> result = peek();
        _data.pop(0);
        _count -= 1;
        build_max_heap(0, _count);
    }

    template<class Key, class Value>
    void binary_heap_t<Key, Value>::insert(Key key, Value value) {
        _data.append(new binary_heap_t<Key, Value>(key, value));
        uint32_t i = _count;
		build_max_heap(0, _count);
		_count += 1;
    }

    template<class Key, class Value>
    std::pair<Key, Value> binary_heap_t<Key, Value>::peek() const {
        return std::make_pair(_data[0]->key, _data[0]->value);
    }
}

#endif
