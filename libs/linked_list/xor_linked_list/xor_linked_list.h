#ifndef XOR_LINKED_LIST_H
#define XOR_LINKED_LIST_H

#include <cstdint>
#include <initializer_list>
#include <functional>

#include "xor_linked_list_node.h"
#include "xor_linked_list_iterator.h"
#include "xor_linked_list_reverse_iterator.h"

namespace mylib {
    template<class Value>
    class xor_linked_list_t {
        private:
            xor_linked_list_node_t<Value>* _head = nullptr;
            xor_linked_list_node_t<Value>* _rear = nullptr;
            uint32_t _count = 0;
            
            xor_linked_list_node_t<Value>* get_node(uint32_t index, xor_linked_list_node_t<Value>** prev_ptr) const;
            
            static xor_linked_list_node_t<Value>* calc_npx(xor_linked_list_node_t<Value>* prev, xor_linked_list_node_t<Value>* next) const;
            
            static xor_linked_list_node_t<Value>* calc_prev(xor_linked_list_node_t<Value>* current, xor_linked_list_node_t<Value>* next) const;
            
            static xor_linked_list_node_t<Value>* calc_next(xor_linked_list_node_t<Value>* current, xor_linked_list_node_t<Value>* prev) const;
        public:
            const uint32_t& length = _count;

            // -----------
            // MANDATORY
            // -----------

            xor_linked_list_t();
            xor_linked_list_t(const xor_linked_list_t<Value>& rhs);
            xor_linked_list_t(xor_linked_list_t<Value>&& rhs);

            virtual ~xor_linked_list_t();

            xor_linked_list_t<Value>& operator=(const xor_linked_list_t<Value>& rhs);
            xor_linked_list_t<Value>& operator=(xor_linked_list_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            void append(Value item);
            template<class... Args> void append(Value item, Args... rest);

            xor_linked_list_iterator_t<Value> begin() const;
            
            void clear();

            xor_linked_list_t<Value>* copy() const;

            uint32_t count(Value item) const;
            
            xor_linked_list_iterator_t<Value> end() const;
            
            template<class Iter> void extend(Iter it);
            void extend(std::initializer_list<Value> elements);
            void extend(Value* arr, uint32_t l, uint32_t r);
            void extend(Value* arr, uint32_t n);

            uint32_t index(Value item, uint32_t start, uint32_t end) const;
            uint32_t index(Value item, uint32_t start) const;
            uint32_t index(Value item) const;

            void insert(uint32_t index, Value item);

            template<class U> bool is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) const;
            template<class U> bool is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key) const;
            bool is_sorted(std::function<int32_t(Value, Value)> cmp) const;
            bool is_sorted() const;

            Value pop(uint32_t index);
            Value pop();
            
            xor_linked_list_reverse_iterator_t<Value> rbegin() const;
            
            void remove(Value item);
            
            xor_linked_list_reverse_iterator_t<Value> rend() const;

            void reverse();

            xor_linked_list_t<Value>* sublist(uint32_t left, uint32_t right, uint32_t step) const;

            Value& operator[](uint32_t index) const;

            template<class Iterator> xor_linked_list_t<Value>* operator+(Iterator rhs) const;
            xor_linked_list_t<Value>* operator+(const xor_linked_list_t<Value>& rhs) const;

            template<class Iterator> xor_linked_list_t<Value>& operator+=(Iterator rhs);
            xor_linked_list_t<Value>& operator+=(const xor_linked_list_t<Value>& rhs);

            xor_linked_list_t<Value>* operator*(uint32_t amount) const;
    };
    
    // -----------
    // PRIVATE
    // -----------
    
    template<class Value>
    xor_linked_list_node_t<Value>* xor_linked_list_t<Value>::get_node(uint32_t index, xor_linked_list_node_t<Value>** prev_ptr) const {
        if(index >= _count) {
            throw "Index out of range";
        }
        
        xor_linked_list_node_t<Value>* prev = nullptr;
        xor_linked_list_node_t<Value>* current = _head;
        xor_linked_list_node_t<Value>* temp;
        uint32_t i = 0;
        
        while(i < index) {
            temp = current;
            current = calc_next(current, prev);
            prev = temp;
            i += 1;
        }
        
        if(prev_ptr) *prev_ptr = prev;
        return current;
    }
    
    template<class Value>
    xor_linked_list_node_t<Value>* xor_linked_list_t<Value>::calc_npx(xor_linked_list_node_t<Value>* prev, xor_linked_list_node_t<Value>* next) const {
        return reinterpret_cast<xor_linked_list_node_t<Value>*>(reinterpret_cast<intptr_t>(prev) ^ reinterpret_cast<intptr_t>(next));
    }
    
    template<class Value>
    xor_linked_list_node_t<Value>* xor_linked_list_t<Value>::calc_prev(xor_linked_list_node_t<Value>* current, xor_linked_list_node_t<Value>* next) const {
        return reinterpret_cast<xor_linked_list_node_t<Value>*>(reinterpret_cast<intptr_t>(current->npx) ^ reinterpret_cast<intptr_t>(next));
    }
    
    template<class Value>
    xor_linked_list_node_t<Value>* xor_linked_list_t<Value>::calc_next(xor_linked_list_node_t<Value>* current, xor_linked_list_node_t<Value>* prev) const {
        return reinterpret_cast<xor_linked_list_node_t<Value>*>(reinterpret_cast<intptr_t>(current->npx) ^ reinterpret_cast<intptr_t>(prev));
    }
    
    // -----------
    // MANDATORY
    // -----------

    template<class Value>
    xor_linked_list_t<Value>::xor_linked_list_t() {}

    template<class Value>
    xor_linked_list_t<Value>::xor_linked_list_t(const xor_linked_list_t<Value>& rhs) {
        for(Value item : rhs) {
            append(item);
        }
    }
    
    template<class Value>
    xor_linked_list_t<Value>::xor_linked_list_t(xor_linked_list_t<Value>&& rhs) {
        _head = rhs._head;
        rhs._head = nullptr;
        
        _rear = rhs._rear;
        rhs._rear = nullptr;
        
        _count = rhs._count;
        rhs._count = 0;
    }

    template<class Value>
    xor_linked_list_t<Value>::~xor_linked_list_t() {
        clear();
    }

    template<class Value>
    xor_linked_list_t<Value>& xor_linked_list_t<Value>::operator=(const xor_linked_list_t<Value>& rhs) {
        clear();
        
        for(Value item : rhs) {
            append(item);
        }
    }

    template<class Value>
    xor_linked_list_t<Value>& xor_linked_list_t<Value>::operator=(xor_linked_list_t<Value>&& rhs) {
        clear();
        
        _head = rhs._head;
        rhs._head = nullptr;
        
        _rear = rhs._rear;
        rhs._rear = nullptr;
        
        _count = rhs._count;
        rhs._count = 0;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Value>
    void xor_linked_list_t<Value>::append(Value item) {
        xor_linked_list_node_t<Value>* node;
        node = new xor_linked_list_node_t<Value>(item);
        node->npx = _rear;
        
        if(_count > 0) {
            _rear->npx = calc_npx(_rear->npx, node);
            _rear = node;
        } else {
            _head = _rear = node;
        }
        
        _count += 1;
    }

    template<class Value>
    template<class... Args>
    void xor_linked_list_t<Value>::append(Value item, Args... rest) {
        append(item);
        append(rest...);
    }
    
    template<class Value>
    xor_linked_list_iterator_t<Value> xor_linked_list_t<Value>::begin() const {
        return xor_linked_list_iterator_t<Value>(_head, nullptr);
    }
            
    template<class Value>
    void xor_linked_list_t<Value>::clear() {
        xor_linked_list_node_t<Value>* prev = nullptr;
        xor_linked_list_node_t<Value>* current = _head;
        xor_linked_list_node_t<Value>* temp;
        
        while(current) {
            temp = calc_next(current, prev);
            prev = current;
            delete current;
            current = temp;
        }
    }

    template<class Value>
    xor_linked_list_t<Value>* xor_linked_list_t<Value>::copy() const {
        return new xor_linked_list_node_t<Value>(*this);
    }
    
    template<class Value>
    uint32_t xor_linked_list_t<Value>::count(Value item) const {
        uint32_t result = 0;
        
        for(Value current : *this) {
            if(current == item) {
                result += 1;
            }
        }
        
        return result;
    }
    
    template<class Value>
    xor_linked_list_iterator_t<Value> xor_linked_list_t<Value>::end() const {
        return xor_linked_list_iterator_t<Value>(nullptr, nullptr);
    }

    template<class Value>
    template<class Iter>
    void xor_linked_list_t<Value>::extend(Iter it) {
        for(Value item : it) {
            append(item);
        }
    }
    
    template<class Value>
    void xor_linked_list_t<Value>::extend(std::initializer_list<Value> elements) {
        for(Value item : elements) {
            append(item);
        }
    }
    
    template<class Value>
    void xor_linked_list_t<Value>::extend(Value* arr, uint32_t l, uint32_t r){
        for(uint32_t i = l; i < r; i += 1) {
            append(arr[i]);
        }
    }
    
    template<class Value>
    void xor_linked_list_t<Value>::extend(Value* arr, uint32_t n){
        extend(arr, 0, n);
    }

    template<class Value>
    uint32_t xor_linked_list_t<Value>::index(Value item, uint32_t start, uint32_t end) const {
        uint32_t i = 0;
        
        for(Value current : *this) {
            if(current == item) {
                return i;
            }
            
            i += 1;
        }
        
        throw "Item not found";
    }
    
    template<class Value>
    uint32_t xor_linked_list_t<Value>::index(Value item, uint32_t start) const {
        return index(item, start, _count);
    }
    
    template<class Value>
    uint32_t xor_linked_list_t<Value>::index(Value item) const {
        return index(item, 0, _count);
    }

    template<class Value>
    void xor_linked_list_t<Value>::insert(uint32_t index, Value item) {
        if(index > _count) {
            throw "Index out of range";
        } else if(index == _count) {
            append(item);
        } else if(index == 0) {
            xor_linked_list_node_t<Value>* node;
            node = new xor_linked_list_node_t<Value>(item);
            node->npx = _head;
            
            if(_count > 0) {
                _head->npx = calc_npx(_head->npx, node);
                _head = node;
            } else {
                _head = _rear = node;
            }
            
            _count += 1;
        } else {
            xor_linked_list_node_t<Value>* node;
            node = new xor_linked_list_node_t<Value>(item);
            node->npx = _head;
            
            xor_linked_list_node_t<Value>* prev = nullptr;
            xor_linked_list_node_t<Value>* current = get_node(index - 1, &prev);
            xor_linked_list_node_t<Value>* next = calc_next(current, prev);
            
            current->npx = calc_npx(calc_prev(current, next), node);
            node->npx = calc_npx(current, next);
            next->npx = calc_npx(node, calc_next(next, current));
            
            _count += 1;
        }
    }

    template<class Value>
    template<class U>
    bool xor_linked_list_t<Value>::is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) const {
        if(_count <= 1) {
            return true;
        } else {
            auto it = begin();
            Value current = *it;
            it += 1;

            while(it != end()) {
                int cmp_r = cmp(key(*it), key(current));
                cmp_r = reverse ? -cmp_r : cmp_r;
                
                if (cmp_r < 0) {
                    return false;
                }

                current = *it;
                it += 1;
            }
        }
    }
    
    template<class Value>
    template<class U>
    bool xor_linked_list_t<Value>::is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key) const {
        return is_sorted(cmp, key, false);
    }
    
    template<class Value>
    bool xor_linked_list_t<Value>::is_sorted(std::function<int32_t(Value, Value)> cmp) const {
        return is_sorted<Value>(cmp, [](Value x) { return x; }, false);
    }
    
    template<class Value>
    bool xor_linked_list_t<Value>::is_sorted() const {
        return is_sorted<Value>([](Value x, Value y) { return x - y; }, [](Value x) { return x; }, false);
    }

    template<class Value>
    Value xor_linked_list_t<Value>::pop(uint32_t index) {
        if (index >= _count) {
            throw "index out of range";
        }
        
        xor_linked_list_node_t<Value> *A, *B, *C, *temp;
        
        B = _head;
        A = nullptr;

        size_t i = 0;

        while(i < index) {
            temp = B;
            B = calc_next(B, A);
            A = temp;
            
            i += 1;
        }

        C = calc_next(B, A);

        if(A)
            A->npx = calc_npx(calc_prev(A, B), C);
        if(C)
            C->npx = calc_npx(A, calc_next(C, B));
        
        Value result = B->value;
        delete B;

        if(index == 0)
            _head = C;
        if(index == (_count - 1))
            _rear = A;

        _count -= 1;
        
        return result;
    }
    
    template<class Value>
    Value xor_linked_list_t<Value>::pop() {
        return pop(_count - 1);
    }
    
    template<class Value>
    xor_linked_list_reverse_iterator_t<Value> xor_linked_list_t<Value>::rbegin() const {
        return xor_linked_list_reverse_iterator_t<Value>(_rear, _rear->npx);
    }
    
    template<class Value>
    void xor_linked_list_t<Value>::remove(Value item) {
        pop(index(item));
    }
    
    template<class Value>
    xor_linked_list_reverse_iterator_t<Value> xor_linked_list_t<Value>::rend() const {
        return xor_linked_list_reverse_iterator_t<Value>(nullptr, nullptr);
    }
    
    template<class Value>
    void xor_linked_list_t<Value>::reverse() {
        std::swap(_head, _rear);
    }

    template<class Value>
    xor_linked_list_t<Value>* xor_linked_list_t<Value>::sublist(uint32_t left, uint32_t right, uint32_t step) const {
        xor_linked_list_t<Value>* result = new xor_linked_list_t<Value>();
        
        xor_linked_list_node_t<Value>* prev = nullptr;
        xor_linked_list_node_t<Value>* current = get_node(left, &prev);
        xor_linked_list_node_t<Value>* temp;
        
        uint32_t i = left;
        
        while(i < right) {
            result->append(current->value);
            
            for(uint32_t j = 0; j < step; j += 1) {
                temp = current;
                current = calc_next(current, prev);
                prev = temp;
            }
            
            i += step;
        }
        
        return result;
    }

    template<class Value>
    Value& xor_linked_list_t<Value>::operator[](uint32_t index) const {
        xor_linked_list_node_t<Value>* node = get_node(index, nullptr);
        return node->value;
    }

    template<class Value>
    template<class Iterator>
    xor_linked_list_t<Value>* xor_linked_list_t<Value>::operator+(Iterator rhs) const {
        xor_linked_list_t<Value>* result = new xor_linked_list_t<Value>(*this);
        
        for(Value item : rhs) {
            result->append(item);
        }
        
        return result;
    }
    
    template<class Value>
    xor_linked_list_t<Value>* xor_linked_list_t<Value>::operator+(const xor_linked_list_t<Value>& rhs) const {
        xor_linked_list_t<Value>* result = new xor_linked_list_t<Value>(*this);
        
        for(Value item : rhs) {
            result->append(item);
        }
        
        return result;
    }

    template<class Value>
    template<class Iterator>
    xor_linked_list_t<Value>& xor_linked_list_t<Value>::operator+=(Iterator rhs) {
        operator=(operator+(rhs));
    }
    
    template<class Value>
    xor_linked_list_t<Value>& xor_linked_list_t<Value>::operator+=(const xor_linked_list_t<Value>& rhs) {
        operator=(operator+(rhs));
    }

    template<class Value>
    xor_linked_list_t<Value>* xor_linked_list_t<Value>::operator*(uint32_t amount) const {
        xor_linked_list_t<Value>* result = xor_linked_list_t<Value>();
        
        for(uint32_t i = 0; i < amount; i += 1) {
            for(Value item : *this) {
                result->append(item);
            }
        }
        
        return result;
    }
}

#endif
