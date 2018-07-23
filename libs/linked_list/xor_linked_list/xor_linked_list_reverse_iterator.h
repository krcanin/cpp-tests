#ifndef XOR_LINKED_LIST_REVERSE_ITERATOR_H
#define XOR_LINKED_LIST_REVERSE_ITERATOR_H

#include "xor_linked_list_node.h"

namespace mylib {
    template<class Value>
    class xor_linked_list_reverse_iterator_t {
        protected:
            xor_linked_list_node_t<Value> *_current, *_prev;
        public:
            // -----------
            // MANDATORY
            // -----------
            
            xor_linked_list_reverse_iterator_t(xor_linked_list_node_t<Value>* current, xor_linked_list_node_t<Value>* prev);
            xor_linked_list_reverse_iterator_t(const xor_linked_list_reverse_iterator_t<Value>& rhs);
            xor_linked_list_reverse_iterator_t(xor_linked_list_reverse_iterator_t<Value>&& rhs);

            xor_linked_list_reverse_iterator_t<Value>& operator=(const xor_linked_list_reverse_iterator_t<Value>& rhs);
            xor_linked_list_reverse_iterator_t<Value>& operator=(xor_linked_list_reverse_iterator_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------
            
            xor_linked_list_reverse_iterator_t<Value> operator++(int); // post-increment
            xor_linked_list_reverse_iterator_t<Value>& operator++(); // pre-increment
            
            bool operator==(xor_linked_list_reverse_iterator_t<Value> rhs);
            bool operator!=(xor_linked_list_reverse_iterator_t<Value> rhs);
            
            Value operator*();
            Value* operator->();
            
            xor_linked_list_reverse_iterator_t<Value> operator--(int); // post-decrement
            xor_linked_list_reverse_iterator_t<Value>& operator--(); // pre-increment
            
            xor_linked_list_reverse_iterator_t<Value> operator+(uint32_t n);
            xor_linked_list_reverse_iterator_t<Value> operator-(uint32_t n);
            
            xor_linked_list_reverse_iterator_t<Value>& operator+=(uint32_t n);
            xor_linked_list_reverse_iterator_t<Value>& operator-=(uint32_t n);
    };
    
    // -----------
    // MANDATORY
    // -----------
    
    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>::xor_linked_list_reverse_iterator_t(xor_linked_list_node_t<Value>* current, xor_linked_list_node_t<Value>* prev) : _current(current), _prev(prev) {}

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>::xor_linked_list_reverse_iterator_t(const xor_linked_list_reverse_iterator_t<Value>& rhs) : _current(rhs._current), _prev(rhs._prev) {}

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>::xor_linked_list_reverse_iterator_t(xor_linked_list_reverse_iterator_t<Value>&& rhs) {
        _current = rhs._current;
        rhs._current = nullptr;
        
        _prev = rhs._prev;
        rhs._prev = nullptr;
    }

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>& xor_linked_list_reverse_iterator_t<Value>::operator=(const xor_linked_list_reverse_iterator_t<Value>& rhs) {
        _current = rhs._current;
        _prev = rhs._prev;
        
        return *this;
    }

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>& xor_linked_list_reverse_iterator_t<Value>::operator=(xor_linked_list_reverse_iterator_t<Value>&& rhs) {
        _current = rhs._current;
        rhs._current = nullptr;
        
        _prev = rhs._prev;
        rhs._prev = nullptr;
        
        return *this;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value> xor_linked_list_reverse_iterator_t<Value>::operator++(int) {
        xor_linked_list_reverse_iterator_t<Value> copy(*this);
        
        operator++();
        
        return copy;
    }

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>& xor_linked_list_reverse_iterator_t<Value>::operator++() {
        xor_linked_list_node_t<Value>* temp = _prev;
        
        if(_prev) {
            _prev = reinterpret_cast<xor_linked_list_node_t<Value>*>(reinterpret_cast<intptr_t>(_prev->npx) ^ reinterpret_cast<intptr_t>(_current));
        } else {
            _prev = nullptr;
        }
        
        _current = temp;
        
        return *this;
    }

    template<class Value>
    bool xor_linked_list_reverse_iterator_t<Value>::operator==(xor_linked_list_reverse_iterator_t<Value> rhs) {
        return _current == rhs._current;
    }

    template<class Value>
    bool xor_linked_list_reverse_iterator_t<Value>::operator!=(xor_linked_list_reverse_iterator_t<Value> rhs) {
        return !(operator==(rhs));
    }

    template<class Value>
    Value xor_linked_list_reverse_iterator_t<Value>::operator*() {
        return *(operator->());
    }

    template<class Value>
    Value* xor_linked_list_reverse_iterator_t<Value>::operator->() {
        return &(_current->value);
    }

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value> xor_linked_list_reverse_iterator_t<Value>::operator--(int) {
        xor_linked_list_reverse_iterator_t<Value> copy(*this);
        
        operator--();
        
        return copy;
    }

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>& xor_linked_list_reverse_iterator_t<Value>::operator--() {
        xor_linked_list_node_t<Value>* temp = _current;
        _current = reinterpret_cast<xor_linked_list_node_t<Value>*>(reinterpret_cast<intptr_t>(_current->npx) ^ reinterpret_cast<intptr_t>(_prev));
        _prev = temp;
        
        return *this;
    }

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value> xor_linked_list_reverse_iterator_t<Value>::operator+(uint32_t n) {
        xor_linked_list_reverse_iterator_t<Value> copy(*this);
        
        for(uint32_t i = 0; i < n; i += 1) {
            copy.operator++();
        }
        
        return copy;
    }

    template<class Value>
    xor_linked_list_reverse_iterator_t<Value> xor_linked_list_reverse_iterator_t<Value>::operator-(uint32_t n) {
        xor_linked_list_reverse_iterator_t<Value> copy(*this);
        
        for(uint32_t i = 0; i < n; i += 1) {
            copy.operator--();
        }
        
        return copy;
    }
    
    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>& xor_linked_list_reverse_iterator_t<Value>::operator+=(uint32_t n) {
        operator=(operator+(n));
    }
    
    template<class Value>
    xor_linked_list_reverse_iterator_t<Value>& xor_linked_list_reverse_iterator_t<Value>::operator-=(uint32_t n) {
        operator=(operator-(n));
    }
}

template<class Value>
crap::xor_linked_list_reverse_iterator_t<Value> operator+(uint32_t n, crap::xor_linked_list_reverse_iterator_t<Value>& rhs);

template<class Value>
crap::xor_linked_list_reverse_iterator_t<Value> operator+(uint32_t n, crap::xor_linked_list_reverse_iterator_t<Value>& rhs) {
    return rhs + n;
}

#endif
