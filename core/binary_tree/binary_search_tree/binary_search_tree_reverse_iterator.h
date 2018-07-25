#ifndef BINARY_SEARCH_TREE_REVERSE_ITERATOR_H
#define BINARY_SEARCH_TREE_REVERSE_ITERATOR_H

#include <cstdint>
#include <utility>

#include "binary_search_tree_node.h"
#include "../../list/list.h"

namespace mylib {
    template<class Key, class Value>
    class binary_search_tree_reverse_iterator_t {
        private:
            std::pair<Key, Value>** _arr = nullptr;
            uint32_t _index = 0;
            uint32_t _n = 0;

            void in_order(binary_search_tree_node_t<Key, Value>* node);
        public:
            // -----------
            // MANDATORY
            // -----------

            binary_search_tree_reverse_iterator_t() = delete;
            binary_search_tree_reverse_iterator_t(const binary_search_tree_reverse_iterator_t<Key, Value>& rhs);
            binary_search_tree_reverse_iterator_t(binary_search_tree_reverse_iterator_t<Key, Value>&& rhs);

            ~binary_search_tree_reverse_iterator_t();

            binary_search_tree_reverse_iterator_t<Key, Value>& operator=(const binary_search_tree_reverse_iterator_t<Key, Value>& rhs);
            binary_search_tree_reverse_iterator_t<Key, Value>& operator=(binary_search_tree_reverse_iterator_t<Key, Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            binary_search_tree_reverse_iterator_t(binary_search_tree_node_t<Key, Value>* node, uint32_t n);

            binary_search_tree_reverse_iterator_t<Key, Value> operator++(int); // post-increment
            binary_search_tree_reverse_iterator_t<Key, Value>& operator++(); // pre-increment

            bool operator==(binary_search_tree_reverse_iterator_t<Key, Value> rhs);
            bool operator!=(binary_search_tree_reverse_iterator_t<Key, Value> rhs);

            std::pair<Key, Value> operator*();

            binary_search_tree_reverse_iterator_t<Key, Value> operator--(int); // post-decrement
            binary_search_tree_reverse_iterator_t<Key, Value>& operator--(); // pre-increment

            binary_search_tree_reverse_iterator_t<Key, Value> operator+(uint32_t n);
            binary_search_tree_reverse_iterator_t<Key, Value> operator-(uint32_t n);

            binary_search_tree_reverse_iterator_t<Key, Value>& operator+=(uint32_t n);
            binary_search_tree_reverse_iterator_t<Key, Value>& operator-=(uint32_t n);
    };

    // -----------
    // PRIVATE
    // -----------

    template<class Key, class Value>
    void binary_search_tree_reverse_iterator_t<Key, Value>::in_order(binary_search_tree_node_t<Key, Value>* node) {
        if(node) {
            in_order(node->right);
            _arr[_index++] = new std::pair<Key, Value>(node->key, node->value);
            in_order(node->left);
        }
    }

    // -----------
    // MANDATORY
    // -----------

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>::binary_search_tree_reverse_iterator_t(const binary_search_tree_reverse_iterator_t<Key, Value>& rhs) {
    	_index = rhs._index;
		_n = rhs._n;

		if(rhs._arr) {
			_arr = new std::pair<Key, Value>*[_n];

			for(uint32_t i = 0; i < _n; i += 1) {
				_arr[i] = new std::pair<Key, Value>(rhs._arr[i]->first, rhs._arr[i]->second);
			}
		}
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>::binary_search_tree_reverse_iterator_t(binary_search_tree_reverse_iterator_t<Key, Value>&& rhs) {
    	_arr = rhs._arr;
		rhs._arr = nullptr;

		_index = rhs._index;
		rhs._index = 0;

		_n = rhs._n;
		rhs._n = 0;
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>::~binary_search_tree_reverse_iterator_t() {
    	if(_arr) {
			for(uint32_t i = 0; i < _n; i += 1) {
				delete _arr[i];
			}

			delete _arr;
    	}
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>& binary_search_tree_reverse_iterator_t<Key, Value>::operator=(const binary_search_tree_reverse_iterator_t<Key, Value>& rhs) {
    	this->~binary_search_tree_reverse_iterator_t();

        _index = rhs._index;
        _n = rhs._n;

        _arr = new std::pair<Key, Value>*[_n];

        for(uint32_t i = 0; i < _n; i += 1) {
        	_arr[i] = new std::pair<Key, Value>(rhs._arr[i]->first, rhs._arr[i]->second);
        }

        return *this;
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>& binary_search_tree_reverse_iterator_t<Key, Value>::operator=(binary_search_tree_reverse_iterator_t<Key, Value>&& rhs) {
    	this->~binary_search_tree_reverse_iterator_t();

        _arr = rhs._arr;
        rhs._arr = nullptr;

        _index = rhs._index;
        rhs._index = 0;

        _n = rhs._n;
        rhs._n = 0;

        return *this;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>::binary_search_tree_reverse_iterator_t(binary_search_tree_node_t<Key, Value>* node, uint32_t n) {
    	if(node) {
			_arr = new std::pair<Key, Value>*[n];
			_n = n;
			_index = 0;

			in_order(node);
			_index = 0;
    	} else {
    		_n = n;
    	}
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value> binary_search_tree_reverse_iterator_t<Key, Value>::operator++(int) {
        binary_search_tree_reverse_iterator_t<Key, Value> copy(*this);

        operator++();

        return copy;
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>& binary_search_tree_reverse_iterator_t<Key, Value>::operator++() {
        operator+=(1);
        return *this;
    }

    template<class Key, class Value>
    bool binary_search_tree_reverse_iterator_t<Key, Value>::operator==(binary_search_tree_reverse_iterator_t<Key, Value> rhs) {
        return _index == rhs._n;
    }

    template<class Key, class Value>
    bool binary_search_tree_reverse_iterator_t<Key, Value>::operator!=(binary_search_tree_reverse_iterator_t<Key, Value> rhs) {
        return !(operator==(rhs));
    }

    template<class Key, class Value>
    std::pair<Key, Value>& binary_search_tree_reverse_iterator_t<Key, Value>::operator*() {
        return *(_arr[_index]);
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value> binary_search_tree_reverse_iterator_t<Key, Value>::operator--(int) {
        binary_search_tree_reverse_iterator_t<Key, Value> copy(*this);

        operator--();

        return copy;
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>& binary_search_tree_reverse_iterator_t<Key, Value>::operator--() {
        operator-=(1);
        return *this;
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value> binary_search_tree_reverse_iterator_t<Key, Value>::operator+(uint32_t n) {
        binary_search_tree_reverse_iterator_t<Key, Value> result(*this);
        result._index += n;
        return result;
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value> binary_search_tree_reverse_iterator_t<Key, Value>::operator-(uint32_t n) {
    	binary_search_tree_reverse_iterator_t<Key, Value> result(*this);
		result._index -= n;
		return result;
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>& binary_search_tree_reverse_iterator_t<Key, Value>::operator+=(uint32_t n) {
        return operator=(operator+(n));
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value>& binary_search_tree_reverse_iterator_t<Key, Value>::operator-=(uint32_t n) {
        return operator=(operator-(n));
    }
}

template<class Key, class Value>
crap::binary_search_tree_reverse_iterator_t<Key, Value> operator+(uint32_t n, crap::binary_search_tree_reverse_iterator_t<Key, Value>& rhs);

template<class Key, class Value>
crap::binary_search_tree_reverse_iterator_t<Key, Value> operator+(uint32_t n, crap::binary_search_tree_reverse_iterator_t<Key, Value>& rhs) {
    return rhs + n;
}

#endif
