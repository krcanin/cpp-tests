#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "binary_heap_node.h"
#include "../../list/list.h"

namespace crap {
    template<class Key, class Value>
    class binary_heap_t {
        private:
            list_t<binary_heap_node<Key, Value>*> _data;
            uint32_t _count = 0;
            std::function<int32_t(Key, Key)> _compare;

            void build_max_heap(uint32_t l, uint32_t r);
            void heapify(uint32_t i);
        public:
            uint32_t& length = _count;

            // -----------
            // MANDATORY
            // -----------

            binary_heap_t(const binary_heap_t<Key, Value>& rhs);
            binary_heap_t(binary_heap_t<Key, Value>&& rhs);

            binary_heap_t<Key, Value>& operator=(const binary_heap_t<Key, Value>& rhs);
            binary_heap_t<Key, Value>& operator=(binary_heap_t<Key, Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            binary_heap_t(std::function<Key, Value> compare);

            std::pair<Key, Value> extract();
            void insert(Key key, Value value);
            std::pair<Key, Value> peek() const;
    };

    // -----------
    // PRIVATE
    // -----------

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

    template<class Key, class Value>
    void binary_heap_t<Key, Value>::build_max_heap(uint32_t l, uint32_t r) {
    	if (l == r) return;

    	uint32_t n = r - l + 1;
    	uint32_t i = l + (n / 2) - 1;

    	bool flag = true;

    	while (i >= l && flag) {
    		heapify(i);

    		if (i == 0) {
    			flag = false;
    		} else {
    			i -= 1;
    		}
    	}
    }

    // -----------
    // MANDATORY
    // -----------

    // -----------
    // USER-DEFINED
    // -----------

}

#endif
