#ifndef SINGLY_LINKED_LIST_ITERATOR_H
#define SINGLY_LINKED_LIST_ITERATOR_H

#include "singly_linked_list_node.h"

namespace crap {
    template<class Value>
    class singly_linked_list_iterator_t {
        private:
            singly_linked_list_node_t<Value>* _node;
        public:
            // -----------
            // MANDATORY
            // -----------
            
            singly_linked_list_iterator_t(singly_linked_list_node_t<Value>* node);
            singly_linked_list_iterator_t(const singly_linked_list_iterator_t<Value>& rhs);
            singly_linked_list_iterator_t(singly_linked_list_iterator_t<Value>&& rhs);

            singly_linked_list_iterator_t<Value>& operator=(const singly_linked_list_iterator_t<Value>& rhs);
            singly_linked_list_iterator_t<Value>& operator=(singly_linked_list_iterator_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------
            
            singly_linked_list_iterator_t<Value> operator++(int); // post-increment
            singly_linked_list_iterator_t<Value>& operator++(); // pre-increment
            
            bool operator==(singly_linked_list_iterator_t<Value> rhs);
            bool operator!=(singly_linked_list_iterator_t<Value> rhs);
            
            Value operator*();
            Value* operator->();
            
            singly_linked_list_iterator_t<Value> operator+(uint32_t n);
            
            singly_linked_list_iterator_t<Value>& operator+=(uint32_t n);
    };
    
    // MANDATORY
    // -----------
    
    template<class Value>
    singly_linked_list_iterator_t<Value>::singly_linked_list_iterator_t(singly_linked_list_node_t<Value>* node) : _node(node) {}

    template<class Value>
    singly_linked_list_iterator_t<Value>::singly_linked_list_iterator_t(const singly_linked_list_iterator_t<Value>& rhs) : _node(rhs._node) {}

    template<class Value>
    singly_linked_list_iterator_t<Value>::singly_linked_list_iterator_t(singly_linked_list_iterator_t<Value>&& rhs) {
        _node = rhs._node;
        rhs._node = nullptr;
    }

    template<class Value>
    singly_linked_list_iterator_t<Value>& singly_linked_list_iterator_t<Value>::operator=(const singly_linked_list_iterator_t<Value>& rhs) {
        _node = rhs._node;
        
        return *this;
    }

    template<class Value>
    singly_linked_list_iterator_t<Value>& singly_linked_list_iterator_t<Value>::operator=(singly_linked_list_iterator_t<Value>&& rhs) {
        _node = rhs._node;
        rhs._node = nullptr;
        
        return *this;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Value>
    singly_linked_list_iterator_t<Value> singly_linked_list_iterator_t<Value>::operator++(int) {
        singly_linked_list_iterator_t<Value> copy(*this);
        operator++();
        return copy;
    }

    template<class Value>
    singly_linked_list_iterator_t<Value>& singly_linked_list_iterator_t<Value>::operator++() {
        _node = !_node ? _node : _node->next;
        return *this;
    }

    template<class Value>
    bool singly_linked_list_iterator_t<Value>::operator==(singly_linked_list_iterator_t<Value> rhs) {
        return _node == rhs._node;
    }

    template<class Value>
    bool singly_linked_list_iterator_t<Value>::operator!=(singly_linked_list_iterator_t<Value> rhs) {
        return !(operator==(rhs));
    }

    template<class Value>
    Value singly_linked_list_iterator_t<Value>::operator*() {
        return *(operator->());
    }

    template<class Value>
    Value* singly_linked_list_iterator_t<Value>::operator->() {
        return &(_node->value);
    }

    template<class Value>
    singly_linked_list_iterator_t<Value> singly_linked_list_iterator_t<Value>::operator+(uint32_t n) {
        singly_linked_list_iterator_t<Value> result(*this);
        
        for(uint32_t i = 0; i < n; i += 1) {
            result.operator++();
        }
        
        return result;
    }

    template<class Value>
    singly_linked_list_iterator_t<Value>& singly_linked_list_iterator_t<Value>::operator+=(uint32_t n) {
        operator=(operator+(n));
    }
}

template<class Value>
crap::singly_linked_list_iterator_t<Value> operator+(uint32_t n, crap::singly_linked_list_iterator_t<Value>& rhs);

template<class Value>
crap::singly_linked_list_iterator_t<Value> operator+(uint32_t n, crap::singly_linked_list_iterator_t<Value>& rhs) {
    return rhs + n;
}

#endif
