#ifndef DOUBLY_LINKED_LIST_REVERSE_ITERATOR_H
#define DOUBLY_LINKED_LIST_REVERSE_ITERATOR_H

namespace mylib {
    template<typename Value>
    class doubly_linked_list_reverse_iterator_t {
        private:
            doubly_linked_list_node_t<Value>* _node;
        public:
            // -----------
            // MANDATORY
            // -----------
            
            doubly_linked_list_reverse_iterator_t(doubly_linked_list_node_t<Value>* node);
            doubly_linked_list_reverse_iterator_t(const doubly_linked_list_reverse_iterator_t<Value>& rhs);
            doubly_linked_list_reverse_iterator_t(doubly_linked_list_reverse_iterator_t<Value>&& rhs);

            doubly_linked_list_reverse_iterator_t<Value>& operator=(const doubly_linked_list_reverse_iterator_t<Value>& rhs);
            doubly_linked_list_reverse_iterator_t<Value>& operator=(doubly_linked_list_reverse_iterator_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------
            
            doubly_linked_list_reverse_iterator_t<Value> operator++(int); // post-increment
            doubly_linked_list_reverse_iterator_t<Value>& operator++(); // pre-increment
            
            bool operator==(doubly_linked_list_reverse_iterator_t<Value> rhs);
            bool operator!=(doubly_linked_list_reverse_iterator_t<Value> rhs);
            
            Value operator*();
            Value* operator->();
            
            doubly_linked_list_reverse_iterator_t<Value> operator--(int); // post-decrement
            doubly_linked_list_reverse_iterator_t<Value>& operator--(); // pre-increment
            
            doubly_linked_list_reverse_iterator_t<Value> operator+(uint32_t n);
            doubly_linked_list_reverse_iterator_t<Value> operator-(uint32_t n);
            
            doubly_linked_list_reverse_iterator_t<Value>& operator+=(uint32_t n);
            doubly_linked_list_reverse_iterator_t<Value>& operator-=(uint32_t n);
    };
    
    // MANDATORY
    // -----------
    
    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>::doubly_linked_list_reverse_iterator_t(doubly_linked_list_node_t<Value>* node) : _node(node) {}

    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>::doubly_linked_list_reverse_iterator_t(const doubly_linked_list_reverse_iterator_t<Value>& rhs) : _node(rhs._node) {}

    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>::doubly_linked_list_reverse_iterator_t(doubly_linked_list_reverse_iterator_t<Value>&& rhs) {
        _node = rhs._node;
        rhs._node = nullptr;
    }

    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>& doubly_linked_list_reverse_iterator_t<Value>::operator=(const doubly_linked_list_reverse_iterator_t<Value>& rhs) {
        _node = rhs._node;
        
        return *this;
    }

    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>& doubly_linked_list_reverse_iterator_t<Value>::operator=(doubly_linked_list_reverse_iterator_t<Value>&& rhs) {
        _node = rhs._node;
        rhs._node = nullptr;
        
        return *this;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value> doubly_linked_list_reverse_iterator_t<Value>::operator++(int) {
        doubly_linked_list_reverse_iterator_t<Value> copy(*this);
        operator++();
        return copy;
    }

    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>& doubly_linked_list_reverse_iterator_t<Value>::operator++() {
        _node = !_node ? _node : _node->prev;
        return *this;
    }

    template<typename Value>
    bool doubly_linked_list_reverse_iterator_t<Value>::operator==(doubly_linked_list_reverse_iterator_t<Value> rhs) {
        return _node == rhs._node;
    }

    template<typename Value>
    bool doubly_linked_list_reverse_iterator_t<Value>::operator!=(doubly_linked_list_reverse_iterator_t<Value> rhs) {
        return !(operator==(rhs));
    }

    template<typename Value>
    Value doubly_linked_list_reverse_iterator_t<Value>::operator*() {
        return *(operator->());
    }

    template<typename Value>
    Value* doubly_linked_list_reverse_iterator_t<Value>::operator->() {
        return &(_node->value);
    }
    
    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value> doubly_linked_list_reverse_iterator_t<Value>::operator--(int) {
        doubly_linked_list_reverse_iterator_t<Value> copy(*this);
        operator--();
        return copy;
    }
    
    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>& doubly_linked_list_reverse_iterator_t<Value>::operator--() {
        _node = !_node ? _node : _node->next;
        return *this;
    }
    
    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value> doubly_linked_list_reverse_iterator_t<Value>::operator+(uint32_t n) {
        doubly_linked_list_reverse_iterator_t<Value> result(*this);
        
        for(uint32_t i = 0; i < n; i += 1) {
            result.operator++();
        }
        
        return result;
    }

    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value> doubly_linked_list_reverse_iterator_t<Value>::operator-(uint32_t n) {
        doubly_linked_list_reverse_iterator_t<Value> result(*this);
        
        for(uint32_t i = 0; i < n; i += 1) {
            result.operator--();
        }
        
        return result;
    }

    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>& doubly_linked_list_reverse_iterator_t<Value>::operator+=(uint32_t n) {
        operator=(operator+(n));
    }
    
    template<typename Value>
    doubly_linked_list_reverse_iterator_t<Value>& doubly_linked_list_reverse_iterator_t<Value>::operator-=(uint32_t n) {
        operator=(operator-(n));
    }
}

template<typename Value>
crap::doubly_linked_list_reverse_iterator_t<Value> operator+(uint32_t n, crap::doubly_linked_list_reverse_iterator_t<Value>& rhs);

template<typename Value>
crap::doubly_linked_list_reverse_iterator_t<Value> operator+(uint32_t n, crap::doubly_linked_list_reverse_iterator_t<Value>& rhs) {
    return rhs + n;
}

#endif
