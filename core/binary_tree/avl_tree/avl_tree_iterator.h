#ifndef AVL_TREE_ITERATOR_H
#define AVL_TREE_ITERATOR_H

#include <cstdint>
#include <utility>

#include "avl_tree_node.h"

namespace mylib {
    template<class Key, class Value>
    class avl_tree_iterator_t {
        private:
            avl_tree_node_t<Key, Value>* _head = nullptr;
            uint32_t _index = 0;

            avl_tree_node_t<Key, Value>* in_order(avl_tree_node_t<Key, Value>* node, int32_t* ptr);
        public:
            // -----------
            // MANDATORY
            // -----------

            avl_tree_iterator_t() = delete;
            avl_tree_iterator_t(const avl_tree_iterator_t<Key, Value>& rhs);
            avl_tree_iterator_t(avl_tree_iterator_t<Key, Value>&& rhs);

            ~avl_tree_iterator_t() = default;

            avl_tree_iterator_t<Key, Value>& operator=(const avl_tree_iterator_t<Key, Value>& rhs);
            avl_tree_iterator_t<Key, Value>& operator=(avl_tree_iterator_t<Key, Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            avl_tree_iterator_t(avl_tree_node_t<Key, Value>* node, uint32_t start_index);

            avl_tree_iterator_t<Key, Value> operator++(int); // post-increment
            avl_tree_iterator_t<Key, Value>& operator++(); // pre-increment

            bool operator==(avl_tree_iterator_t<Key, Value> rhs);
            bool operator!=(avl_tree_iterator_t<Key, Value> rhs);

            std::pair<Key, Value> operator*();

            avl_tree_iterator_t<Key, Value> operator--(int); // post-decrement
            avl_tree_iterator_t<Key, Value>& operator--(); // pre-increment

            avl_tree_iterator_t<Key, Value> operator+(uint32_t n);
            avl_tree_iterator_t<Key, Value> operator-(uint32_t n);

            avl_tree_iterator_t<Key, Value>& operator+=(uint32_t n);
            avl_tree_iterator_t<Key, Value>& operator-=(uint32_t n);
    };

    // -----------
    // PRIVATE
    // -----------

    template<class Key, class Value>
    avl_tree_node_t<Key, Value>* avl_tree_iterator_t<Key, Value>::in_order(avl_tree_node_t<Key, Value>* node, int32_t* ptr) {
        if(node) {
            avl_tree_node_t<Key, Value>* result;

            if(result = in_order(node->left, ptr)) {
                return result;
            }

            if(*ptr == _index) {
                return node;
            }

            *ptr += 1;

            if(result = in_order(node->right, ptr)) {
                return result;
            }

            return nullptr;
        } else {
            return nullptr;
        }
    }

    // -----------
    // MANDATORY
    // -----------

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>::avl_tree_iterator_t(const avl_tree_iterator_t<Key, Value>& rhs) {
        _head = rhs._head;
    	_index = rhs._index;
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>::avl_tree_iterator_t(avl_tree_iterator_t<Key, Value>&& rhs) {
        _head = rhs._head;
        rhs._head = nullptr;

        _index = rhs._index;
        rhs._index = 0;
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>& avl_tree_iterator_t<Key, Value>::operator=(const avl_tree_iterator_t<Key, Value>& rhs) {
    	this->~avl_tree_iterator_t();

        _head = rhs._head;
        _index = rhs._index;

        return *this;
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>& avl_tree_iterator_t<Key, Value>::operator=(avl_tree_iterator_t<Key, Value>&& rhs) {
    	this->~avl_tree_iterator_t();

        _head = rhs._head;
        rhs._head = nullptr;

        _index = rhs._index;
        rhs._index = 0;

        return *this;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>::avl_tree_iterator_t(avl_tree_node_t<Key, Value>* node, uint32_t start_index) : _head(node), _index(start_index) {}

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value> avl_tree_iterator_t<Key, Value>::operator++(int) {
        avl_tree_iterator_t<Key, Value> copy(*this);

        operator++();

        return copy;
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>& avl_tree_iterator_t<Key, Value>::operator++() {
        operator+=(1);
        return *this;
    }

    template<class Key, class Value>
    bool avl_tree_iterator_t<Key, Value>::operator==(avl_tree_iterator_t<Key, Value> rhs) {
        return _head == rhs._head && _index == rhs._index;
    }

    template<class Key, class Value>
    bool avl_tree_iterator_t<Key, Value>::operator!=(avl_tree_iterator_t<Key, Value> rhs) {
        return !(operator==(rhs));
    }

    template<class Key, class Value>
    std::pair<Key, Value> avl_tree_iterator_t<Key, Value>::operator*() {
        int32_t* ptr = new int32_t(0);
        avl_tree_node_t<Key, Value>* node = in_order(_head, ptr);
        delete ptr;
        return std::make_pair(node->key, node->value);
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value> avl_tree_iterator_t<Key, Value>::operator--(int) {
        avl_tree_iterator_t<Key, Value> copy(*this);

        operator--();

        return copy;
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>& avl_tree_iterator_t<Key, Value>::operator--() {
        operator-=(1);
        return *this;
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value> avl_tree_iterator_t<Key, Value>::operator+(uint32_t n) {
        avl_tree_iterator_t<Key, Value> result(*this);
        result._index += n;
        return result;
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value> avl_tree_iterator_t<Key, Value>::operator-(uint32_t n) {
    	avl_tree_iterator_t<Key, Value> result(*this);
		result._index -= n;
		return result;
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>& avl_tree_iterator_t<Key, Value>::operator+=(uint32_t n) {
        return operator=(operator+(n));
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value>& avl_tree_iterator_t<Key, Value>::operator-=(uint32_t n) {
        return operator=(operator-(n));
    }
}

template<class Key, class Value>
crap::avl_tree_iterator_t<Key, Value> operator+(uint32_t n, crap::avl_tree_iterator_t<Key, Value>& rhs);

template<class Key, class Value>
crap::avl_tree_iterator_t<Key, Value> operator+(uint32_t n, crap::avl_tree_iterator_t<Key, Value>& rhs) {
    return rhs + n;
}

#endif
