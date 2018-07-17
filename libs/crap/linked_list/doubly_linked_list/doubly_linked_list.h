#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <initializer_list>
#include <functional>

#include "doubly_linked_list_node.h"
#include "doubly_linked_list_iterator.h"
#include "doubly_linked_list_reverse_iterator.h"

namespace crap {
    template<class Value>
    class doubly_linked_list_t {
        private:
            doubly_linked_list_node_t<Value>* _head = nullptr;
            doubly_linked_list_node_t<Value>* _rear = nullptr;
            uint32_t _count = 0;
            
            doubly_linked_list_node_t<Value>* get_node(uint32_t index) const;
            
            template<class U> doubly_linked_list_node_t<Value>* merge_sort(doubly_linked_list_node_t<Value>* head, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse);
            
            template<class U> doubly_linked_list_node_t<Value>* merge(doubly_linked_list_node_t<Value>* first, doubly_linked_list_node_t<Value>* last, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse);
            
            doubly_linked_list_node_t<Value>* split(doubly_linked_list_node_t<Value>* head) const;
        public:
            const uint32_t& length = _count;

            // -----------
            // MANDATORY
            // -----------

            doubly_linked_list_t();
            doubly_linked_list_t(const doubly_linked_list_t<Value>& rhs);
            doubly_linked_list_t(doubly_linked_list_t<Value>&& rhs);

            virtual ~doubly_linked_list_t();

            doubly_linked_list_t<Value>& operator=(const doubly_linked_list_t<Value>& rhs);
            doubly_linked_list_t<Value>& operator=(doubly_linked_list_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            void append(Value item);
            template<class... Args> void append(Value item, Args... rest);

            doubly_linked_list_iterator_t<Value> begin() const;
            
            void clear();

            doubly_linked_list_t<Value>* copy() const;

            uint32_t count(Value item) const;
            
            doubly_linked_list_iterator_t<Value> end() const;
            
            template<class Iterator> void extend(Iterator it);
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

            doubly_linked_list_reverse_iterator_t<Value> rbegin() const;
            
            void remove(Value item);
            
            doubly_linked_list_reverse_iterator_t<Value> rend() const;

            void reverse();

            template<class U> void sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key, bool reverse);
            template<class U> void sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key);
            void sort(std::function<int32_t(Value, Value)> cmp);
            void sort();

            doubly_linked_list_t<Value>* sublist(uint32_t left, uint32_t right, uint32_t step) const;

            Value& operator[](uint32_t index) const;

            template<class Iterator> doubly_linked_list_t<Value>* operator+(Iterator rhs) const;
            doubly_linked_list_t<Value>* operator+(const doubly_linked_list_t<Value>& rhs) const;

            template<class Iterator> doubly_linked_list_t<Value>& operator+=(Iterator rhs);
            doubly_linked_list_t<Value>& operator+=(const doubly_linked_list_t<Value>& rhs);

            doubly_linked_list_t<Value>* operator*(uint32_t amount) const;
    };
    
    // -----------
    // PRIVATE
    // -----------
    
    template<class Value>
    doubly_linked_list_node_t<Value>* doubly_linked_list_t<Value>::get_node(uint32_t index) const {
        if(index >= _count) {
            throw "Index out of range";
        }
        
        uint32_t median = _count / 2;
        
        doubly_linked_list_node_t<Value>* current = nullptr;
        
        if(index < median) {
            current = _head;
            uint32_t i = 0;

            while(i < index) {
                current = current->next;
                i += 1;
            }
        } else {
            current = _rear;
            
            uint32_t i = _count - 1;
            
            while(i > index) {
                current = current->prev;
                i -= 1;
            }
        }
        
        return current;
    }
    
    template<class Value>
    template<class U>
    doubly_linked_list_node_t<Value>* doubly_linked_list_t<Value>::merge_sort(doubly_linked_list_node_t<Value>* head, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) {
        if(!head || !head->next) {
            return head;
        } else {
            doubly_linked_list_node_t<Value>* second = split(head);

            head = merge_sort(head, cmp, key, reverse);
            second = merge_sort(second, cmp, key, reverse);

            return merge(head, second, cmp, key, reverse);
        }
    }
 
    template<class Value>
    template<class U>
    doubly_linked_list_node_t<Value>* doubly_linked_list_t<Value>::merge(doubly_linked_list_node_t<Value>* first, doubly_linked_list_node_t<Value>* second, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) {
        if(!first) {
            return second;
        } else if(!second) {
            return first;
        } else {
            int cmp_r = cmp(key(first->value), key(second->value));
            cmp_r = reverse ? -cmp_r : cmp_r;
            
            if(cmp_r < 0) {
                first->next = merge(first->next, second, cmp, key, reverse);
                first->next->prev = first;
                first->prev = nullptr;
                
                return first;
            } else {
                second->next = merge(first, second->next, cmp, key, reverse);
                second->next->prev = second;
                second->prev = nullptr;
                
                return second;
            }
        }
    }

    template<class Value>
    doubly_linked_list_node_t<Value>* doubly_linked_list_t<Value>::split(doubly_linked_list_node_t<Value>* head) const {
        doubly_linked_list_node_t<Value>* fast = head;
        doubly_linked_list_node_t<Value>* slow = head;
        
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        
        doubly_linked_list_node_t<Value>* result = slow->next;
        slow->next = nullptr;
        
        return result;
    }
 
    // -----------
    // MANDATORY
    // -----------

    template<class Value>
    doubly_linked_list_t<Value>::doubly_linked_list_t() {}

    template<class Value>
    doubly_linked_list_t<Value>::doubly_linked_list_t(const doubly_linked_list_t<Value>& rhs) {
        for(Value item : rhs) {
            append(item);
        }
    }
    
    template<class Value>
    doubly_linked_list_t<Value>::doubly_linked_list_t(doubly_linked_list_t<Value>&& rhs) {
        _head = rhs._head;
        rhs._head = nullptr;
        
        _rear = rhs._rear;
        rhs._head = nullptr;
        
        _count = rhs._count;
        rhs._count = 0;
    }

    template<class Value>
    doubly_linked_list_t<Value>::~doubly_linked_list_t() {
        clear();
    }

    template<class Value>
    doubly_linked_list_t<Value>& doubly_linked_list_t<Value>::operator=(const doubly_linked_list_t<Value>& rhs) {
        clear();
        
        for(Value item : rhs) {
            append(item);
        }
    }

    template<class Value>
    doubly_linked_list_t<Value>& doubly_linked_list_t<Value>::operator=(doubly_linked_list_t<Value>&& rhs) {
        clear();
        
        _head = rhs._head;
        rhs._head = nullptr;
        
        _rear = rhs._rear;
        rhs._head = nullptr;
        
        _count = rhs._count;
        rhs._count = 0;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Value>
    void doubly_linked_list_t<Value>::append(Value item) {
        doubly_linked_list_node_t<Value>* node = new doubly_linked_list_node_t<Value>(item);
        
        if(_count > 0) {
            _rear->next = node;
            _rear = node;
        } else {
            _head = _rear = node;
        }
        
        _count += 1;
    }

    template<class Value>
    template<class... Args>
    void doubly_linked_list_t<Value>::append(Value item, Args... rest) {
        append(item);
        append(rest...);
    }
    
    template<class Value>
    doubly_linked_list_iterator_t<Value> doubly_linked_list_t<Value>::begin() const {
        return doubly_linked_list_iterator_t<Value>(_head);
    }
            
    template<class Value>
    void doubly_linked_list_t<Value>::clear() {
        doubly_linked_list_node_t<Value> *current, *next;
        
        current = _head;
        
        while(current) {
            next = current->next;
            delete current;
            current = next;
        }
        
        _head = _rear = nullptr;
        _count = 0;
    }

    template<class Value>
    doubly_linked_list_t<Value>* doubly_linked_list_t<Value>::copy() const {
        return new doubly_linked_list_t<Value>(*this);
    }

    template<class Value>
    uint32_t doubly_linked_list_t<Value>::count(Value item) const {
        uint32_t result = 0;
        
        for(Value current : *this) {
            if(current == item) {
                result += 1;
            }
        }
        
        return result;
    }

    template<class Value>
    doubly_linked_list_iterator_t<Value> doubly_linked_list_t<Value>::end() const {
        return doubly_linked_list_iterator_t<Value>(nullptr);
    }

    template<class Value>
    template<class Iterator>
    void doubly_linked_list_t<Value>::extend(Iterator it) {
        for(Value item : it) {
            append(item);
        }
    }
    
    template<class Value>
    void doubly_linked_list_t<Value>::extend(std::initializer_list<Value> elements) {
        for(Value item : elements) {
            append(item);
        }
    }
    
    template<class Value>
    void doubly_linked_list_t<Value>::extend(Value* arr, uint32_t l, uint32_t r){
        for(uint32_t i = l; i < r; i += 1) {
            append(arr[i]);
        }
    }
    
    template<class Value>
    void doubly_linked_list_t<Value>::extend(Value* arr, uint32_t n){
        extend(arr, 0, n);
    }

    template<class Value>
    uint32_t doubly_linked_list_t<Value>::index(Value item, uint32_t start, uint32_t end) const {
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
    uint32_t doubly_linked_list_t<Value>::index(Value item, uint32_t start) const {
        return index(item, start, _count);
    }
    
    template<class Value>
    uint32_t doubly_linked_list_t<Value>::index(Value item) const {
        return index(item, 0, _count);
    }

    template<class Value>
    void doubly_linked_list_t<Value>::insert(uint32_t index, Value item) {
        doubly_linked_list_node_t<Value>* node = new doubly_linked_list_node_t<Value>(item);
        
        if(index > 0) {
            doubly_linked_list_node_t<Value>* prev = get_node(index - 1);

            node->next = prev->next;
            prev->next = node;
        } else {
            node->next = _head;
            _head = node;
        }
        
        if(index == _count) {
            _rear = node;
        }
        
        _count += 1;
    }

    template<class Value>
    template<class U>
    bool doubly_linked_list_t<Value>::is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) const {
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
    bool doubly_linked_list_t<Value>::is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key) const {
        return is_sorted(cmp, key, false);
    }
    
    template<class Value>
    bool doubly_linked_list_t<Value>::is_sorted(std::function<int32_t(Value, Value)> cmp) const {
        return is_sorted<Value>(cmp, [](Value x) { return x; }, false);
    }
    
    template<class Value>
    bool doubly_linked_list_t<Value>::is_sorted() const {
        return is_sorted<Value>([](Value x, Value y) { return x - y; }, [](Value x) { return x; }, false);
    }

    template<class Value>
    Value doubly_linked_list_t<Value>::pop(uint32_t index) {
        if(index >= _count) {
            throw "Index out of range";
        }
        
        _count -= 1;
        
        if(index == 0) {
            Value result = _head->value;
            
            singly_linked_list_node_t<Value>* next = _head->next;
            delete _head;
            _head = next;
            
            return result;
        } else {
            singly_linked_list_node_t<Value>* prev = get_node(index - 1);
            singly_linked_list_node_t<Value>* current = prev->next;
            singly_linked_list_node_t<Value>* next = current->next;
            
            Value result = current->value;
            
            delete current;
            prev->next = next;
            
            if(index == (_count - 1)) {
                _rear = prev;
            }
            
            return result;
        }
    }
    
    template<class Value>
    Value doubly_linked_list_t<Value>::pop() {
        return pop(_count - 1);
    }

    template<class Value>
    doubly_linked_list_reverse_iterator_t<Value> doubly_linked_list_t<Value>::rbegin() const {
        return doubly_linked_list_reverse_iterator_t<Value>(_rear);
    }

    template<class Value>
    void doubly_linked_list_t<Value>::remove(Value item) {
        pop(index(item));
    }

    template<class Value>
    doubly_linked_list_reverse_iterator_t<Value> doubly_linked_list_t<Value>::rend() const {
        return doubly_linked_list_reverse_iterator_t<Value>(nullptr);
    }
    
    template<class Value>
    void doubly_linked_list_t<Value>::reverse() {
        if(_count > 1) {
            doubly_linked_list_node_t<Value> *prev, *current, *next;
            
            prev = nullptr;
            current = _head;
            next = _head->next;
            
            while(current) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            
            std::swap(_head, _rear);
        }
    }

    template<class Value>
    template<class U>
    void doubly_linked_list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key, bool reverse) {
        // https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/
        _head = merge_sort(_head, cmp, key, reverse);
        
        _rear = _head;
        
        if(_rear) {
            while(_rear->next) {
                _rear = _rear->next;
            }
        }
    }
    
    template<class Value>
    template<class U>
    void doubly_linked_list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key) {
        sort(cmp, key, false);
    }
    
    template<class Value>
    void doubly_linked_list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp) {
        sort<Value>(cmp, [](Value x) { return x; }, false);
    }
    
    template<class Value>
    void doubly_linked_list_t<Value>::sort() {
        sort<Value>([](Value x, Value y) { return x - y; }, [](Value x) { return x; }, false);
    }

    template<class Value>
    doubly_linked_list_t<Value>* doubly_linked_list_t<Value>::sublist(uint32_t left, uint32_t right, uint32_t step) const {
        if(left >= _count) {
            throw "Invalid left index";
        }
        
        if(right >= _count) {
            throw "Invalid right index";
        }
        
        doubly_linked_list_t<Value>* result = new doubly_linked_list_t<Value>();
        
        doubly_linked_list_node_t<Value>* node = get_node(left);
        uint32_t i = left;
        
        while(i < right) {
            result->append(node->value);
            
            for(uint32_t j = 0; j < step; j += 1) {
                node = node->next;
            }
            
            i += 1;
        }
        
        return result;
    }

    template<class Value>
    Value& doubly_linked_list_t<Value>::operator[](uint32_t index) const {
        doubly_linked_list_node_t<Value>* node = get_node(index);
        return node->value;
    }

    template<class Value>
    template<class Iterator>
    doubly_linked_list_t<Value>* doubly_linked_list_t<Value>::operator+(Iterator rhs) const {
        doubly_linked_list_t<Value>* result = new doubly_linked_list_t<Value>(*this);
        
        for(Value item : rhs) {
            result->append(item);
        }
        
        return result;
    }
    
    template<class Value>
    doubly_linked_list_t<Value>* doubly_linked_list_t<Value>::operator+(const doubly_linked_list_t<Value>& rhs) const {
        doubly_linked_list_t<Value>* result = new doubly_linked_list_t<Value>(*this);
        
        for(Value item : rhs) {
            result->append(item);
        }
        
        return result;
    }

    template<class Value>
    template<class Iterator>
    doubly_linked_list_t<Value>& doubly_linked_list_t<Value>::operator+=(Iterator rhs) {
        for(Value item : rhs) {
            append(item);
        }
        
        return *this;
    }
    
    template<class Value>
    doubly_linked_list_t<Value>& doubly_linked_list_t<Value>::operator+=(const doubly_linked_list_t<Value>& rhs) {
        for(Value item : rhs) {
            append(item);
        }
        
        return *this;
    }

    template<class Value>
    doubly_linked_list_t<Value>* doubly_linked_list_t<Value>::operator*(uint32_t amount) const {
        doubly_linked_list_t<Value>* result = new doubly_linked_list_t<Value>();
        
        for(uint32_t i = 0; i < amount; i += 1) {
            for(Value item : *this) {
                result->append(item);
            }
        }
        
        return result;
    }
}

#endif
