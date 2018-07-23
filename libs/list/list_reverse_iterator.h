#ifndef LIST_REVERSE_ITERATOR_H
#define LIST_REVERSE_ITERATOR_H

#include <cstdint>

namespace mylib {
    template<class Value>
    class list_reverse_iterator_t {
        protected:
            Value** _elements;
            uint32_t _index;
            uint32_t _count;
        public:
            // -----------
            // MANDATORY
            // -----------
            
            list_reverse_iterator_t(Value** elements, uint32_t index, uint32_t count);
            list_reverse_iterator_t(const list_reverse_iterator_t<Value>& rhs);
            list_reverse_iterator_t(list_reverse_iterator_t<Value>&& rhs);

            list_reverse_iterator_t<Value>& operator=(const list_reverse_iterator_t<Value>& rhs);
            list_reverse_iterator_t<Value>& operator=(list_reverse_iterator_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------
            
            list_reverse_iterator_t<Value> operator++(int); // post-increment
            list_reverse_iterator_t<Value>& operator++(); // pre-increment
            
            bool operator==(list_reverse_iterator_t<Value> rhs);
            bool operator!=(list_reverse_iterator_t<Value> rhs);
            
            Value operator*();
            Value* operator->();
            
            list_reverse_iterator_t<Value> operator--(int); // post-decrement
            list_reverse_iterator_t<Value>& operator--(); // pre-increment
            
            list_reverse_iterator_t<Value> operator+(uint32_t n);
            list_reverse_iterator_t<Value> operator-(uint32_t n);
            
            list_reverse_iterator_t<Value>& operator+=(uint32_t n);
            list_reverse_iterator_t<Value>& operator-=(uint32_t n);
    };
    
    // -----------
    // MANDATORY
    // -----------
    
    template<class Value>
    list_reverse_iterator_t<Value>::list_reverse_iterator_t(Value** elements, uint32_t index, uint32_t count) : _elements(elements), _index(index), _count(count) {}

    template<class Value>
    list_reverse_iterator_t<Value>::list_reverse_iterator_t(const list_reverse_iterator_t<Value>& rhs) : _elements(rhs._elements), _index(rhs._index), _count(rhs._count) {}

    template<class Value>
    list_reverse_iterator_t<Value>::list_reverse_iterator_t(list_reverse_iterator_t<Value>&& rhs) {
        _elements = rhs._elements;
        rhs._elements = nullptr;
        
        _index = rhs._index;
        rhs._index = 0;
        
        _count = rhs._count;
        rhs._count = 0;
    }

    template<class Value>
    list_reverse_iterator_t<Value>& list_reverse_iterator_t<Value>::operator=(const list_reverse_iterator_t<Value>& rhs) {
        _elements = rhs._elements;
        _index = rhs._index;
        _count = rhs._count;
        
        return *this;
    }

    template<class Value>
    list_reverse_iterator_t<Value>& list_reverse_iterator_t<Value>::operator=(list_reverse_iterator_t<Value>&& rhs) {
        _elements = rhs._elements;
        rhs._elements = nullptr;
        
        _index = rhs._index;
        rhs._index = 0;
        
        _count = rhs._count;
        rhs._count = 0;
        
        return *this;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Value>
    list_reverse_iterator_t<Value> list_reverse_iterator_t<Value>::operator++(int) {
        list_reverse_iterator_t<Value> copy(*this);
        
        operator++();
        
        return copy;
    }

    template<class Value>
    list_reverse_iterator_t<Value>& list_reverse_iterator_t<Value>::operator++() {
        if(_index == 0) {
            _elements = nullptr;
        } else {
            _index -= 1;
        }
        
        return *this;
    }

    template<class Value>
    bool list_reverse_iterator_t<Value>::operator==(list_reverse_iterator_t<Value> rhs) {
        return _elements == rhs._elements;
    }

    template<class Value>
    bool list_reverse_iterator_t<Value>::operator!=(list_reverse_iterator_t<Value> rhs) {
        return !(operator==(rhs));
    }

    template<class Value>
    Value list_reverse_iterator_t<Value>::operator*() {
        return *(operator->());
    }

    template<class Value>
    Value* list_reverse_iterator_t<Value>::operator->() {
        return _elements[_index];
    }

    template<class Value>
    list_reverse_iterator_t<Value> list_reverse_iterator_t<Value>::operator--(int) {
        list_reverse_iterator_t<Value> copy(*this);
        operator--();
        return copy;
    }

    template<class Value>
    list_reverse_iterator_t<Value>& list_reverse_iterator_t<Value>::operator--() {
        if(_index == (_count - 1)) {
            _elements = nullptr;
        } else {
            _index += 1;
        }
        
        return *this;
    }

    template<class Value>
    list_reverse_iterator_t<Value> list_reverse_iterator_t<Value>::operator+(uint32_t n) {
        list_reverse_iterator_t<Value> result(*this);
        
        if(n > result._index) {
            result._elements = nullptr;
        } else {
            result._index -= n;
        }
        
        return result;
    }

    template<class Value>
    list_reverse_iterator_t<Value> list_reverse_iterator_t<Value>::operator-(uint32_t n) {
        list_reverse_iterator_t<Value> result(*this);
        
        if((result._count - n) <= result._index) {
            result._elements = nullptr;
        } else {
            result._index += n;
        }
        
        return result;
    }
    
    template<class Value>
    list_reverse_iterator_t<Value>& list_reverse_iterator_t<Value>::operator+=(uint32_t n) {
        operator=(operator+(n));
    }
    
    template<class Value>
    list_reverse_iterator_t<Value>& list_reverse_iterator_t<Value>::operator-=(uint32_t n) {
        operator=(operator-(n));
    }
}

template<class Value>
crap::list_reverse_iterator_t<Value> operator+(uint32_t n, crap::list_reverse_iterator_t<Value>& rhs);

template<class Value>
crap::list_reverse_iterator_t<Value> operator+(uint32_t n, crap::list_reverse_iterator_t<Value>& rhs) {
    return rhs + n;
}

#endif
