#ifndef AVL_TREE_REVERSE_ITERATOR_H
#define AVL_TREE_REVERSE_ITERATOR_H

#include <cstdint>
#include <utility>

#include "avl_tree_node.h"
#include "../../list/list.h"

namespace crap {
    template<class Key, class Value>
    class avl_tree_reverse_iterator_t {
        private:
            std::pair<Key, Value>** _arr = nullptr;
            uint32_t _index = 0;
            uint32_t _n = 0;

            void in_order(avl_tree_node_t<Key, Value>* node);
        public:
            // -----------
            // MANDATORY
            // -----------

            avl_tree_reverse_iterator_t() = delete;
            avl_tree_reverse_iterator_t(const avl_tree_reverse_iterator_t<Key, Value>& rhs);
            avl_tree_reverse_iterator_t(avl_tree_reverse_iterator_t<Key, Value>&& rhs);

            ~avl_tree_reverse_iterator_t();

            avl_tree_reverse_iterator_t<Key, Value>& operator=(const avl_tree_reverse_iterator_t<Key, Value>& rhs);
            avl_tree_reverse_iterator_t<Key, Value>& operator=(avl_tree_reverse_iterator_t<Key, Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            avl_tree_reverse_iterator_t(avl_tree_node_t<Key, Value>* node, uint32_t n);

            avl_tree_reverse_iterator_t<Key, Value> operator++(int); // post-increment
            avl_tree_reverse_iterator_t<Key, Value>& operator++(); // pre-increment

            bool operator==(avl_tree_reverse_iterator_t<Key, Value> rhs);
            bool operator!=(avl_tree_reverse_iterator_t<Key, Value> rhs);

            std::pair<Key, Value>& operator*();
            std::pair<Key, Value>* operator->();

            avl_tree_reverse_iterator_t<Key, Value> operator--(int); // post-decrement
            avl_tree_reverse_iterator_t<Key, Value>& operator--(); // pre-increment

            avl_tree_reverse_iterator_t<Key, Value> operator+(uint32_t n);
            avl_tree_reverse_iterator_t<Key, Value> operator-(uint32_t n);

            avl_tree_reverse_iterator_t<Key, Value>& operator+=(uint32_t n);
            avl_tree_reverse_iterator_t<Key, Value>& operator-=(uint32_t n);
    };

    // -----------
    // PRIVATE
    // -----------

    template<class Key, class Value>
    void avl_tree_reverse_iterator_t<Key, Value>::in_order(avl_tree_node_t<Key, Value>* node) {
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
    avl_tree_reverse_iterator_t<Key, Value>::avl_tree_reverse_iterator_t(const avl_tree_reverse_iterator_t<Key, Value>& rhs) {
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
    avl_tree_reverse_iterator_t<Key, Value>::avl_tree_reverse_iterator_t(avl_tree_reverse_iterator_t<Key, Value>&& rhs) {
    	_arr = rhs._arr;
		rhs._arr = nullptr;

		_index = rhs._index;
		rhs._index = 0;

		_n = rhs._n;
		rhs._n = 0;
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value>::~avl_tree_reverse_iterator_t() {
    	if(_arr) {
			for(uint32_t i = 0; i < _n; i += 1) {
				delete _arr[i];
			}

			delete _arr;
    	}
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value>& avl_tree_reverse_iterator_t<Key, Value>::operator=(const avl_tree_reverse_iterator_t<Key, Value>& rhs) {
    	this->~avl_tree_reverse_iterator_t();

        _index = rhs._index;
        _n = rhs._n;

        _arr = new std::pair<Key, Value>*[_n];

        for(uint32_t i = 0; i < _n; i += 1) {
        	_arr[i] = new std::pair<Key, Value>(rhs._arr[i]->first, rhs._arr[i]->second);
        }

        return *this;
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value>& avl_tree_reverse_iterator_t<Key, Value>::operator=(avl_tree_reverse_iterator_t<Key, Value>&& rhs) {
    	this->~avl_tree_reverse_iterator_t();

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
    avl_tree_reverse_iterator_t<Key, Value>::avl_tree_reverse_iterator_t(avl_tree_node_t<Key, Value>* node, uint32_t n) {
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
    avl_tree_reverse_iterator_t<Key, Value> avl_tree_reverse_iterator_t<Key, Value>::operator++(int) {
        avl_tree_reverse_iterator_t<Key, Value> copy(*this);

        operator++();

        return copy;
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value>& avl_tree_reverse_iterator_t<Key, Value>::operator++() {
        operator+=(1);
        return *this;
    }

    template<class Key, class Value>
    bool avl_tree_reverse_iterator_t<Key, Value>::operator==(avl_tree_reverse_iterator_t<Key, Value> rhs) {
        return _index == rhs._n;
    }

    template<class Key, class Value>
    bool avl_tree_reverse_iterator_t<Key, Value>::operator!=(avl_tree_reverse_iterator_t<Key, Value> rhs) {
        return !(operator==(rhs));
    }

    template<class Key, class Value>
    std::pair<Key, Value>& avl_tree_reverse_iterator_t<Key, Value>::operator*() {
        return *(operator->());
    }

    template<class Key, class Value>
    std::pair<Key, Value>* avl_tree_reverse_iterator_t<Key, Value>::operator->() {
        return _arr[_index];
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value> avl_tree_reverse_iterator_t<Key, Value>::operator--(int) {
        avl_tree_reverse_iterator_t<Key, Value> copy(*this);

        operator--();

        return copy;
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value>& avl_tree_reverse_iterator_t<Key, Value>::operator--() {
        operator-=(1);
        return *this;
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value> avl_tree_reverse_iterator_t<Key, Value>::operator+(uint32_t n) {
        avl_tree_reverse_iterator_t<Key, Value> result(*this);
        result._index += n;
        return result;
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value> avl_tree_reverse_iterator_t<Key, Value>::operator-(uint32_t n) {
    	avl_tree_reverse_iterator_t<Key, Value> result(*this);
		result._index -= n;
		return result;
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value>& avl_tree_reverse_iterator_t<Key, Value>::operator+=(uint32_t n) {
        return operator=(operator+(n));
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value>& avl_tree_reverse_iterator_t<Key, Value>::operator-=(uint32_t n) {
        return operator=(operator-(n));
    }
}

template<class Key, class Value>
crap::avl_tree_reverse_iterator_t<Key, Value> operator+(uint32_t n, crap::avl_tree_reverse_iterator_t<Key, Value>& rhs);

template<class Key, class Value>
crap::avl_tree_reverse_iterator_t<Key, Value> operator+(uint32_t n, crap::avl_tree_reverse_iterator_t<Key, Value>& rhs) {
    return rhs + n;
}

#endif
