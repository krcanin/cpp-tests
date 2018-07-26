#ifndef STACK_H
#define STACK_H

#include <cstdint>

#include "singly_linked_list.h"

namespace mylib {
    template<typename Value>
    class stack_t {
        private:
            singly_linked_list_t<Value>* _elements;
        public:
            // -----------
            // MANDATORY
            // -----------

            stack_t();
            stack_t(const stack_t<Value>& rhs);
            stack_t(stack_t<Value>&& rhs);

            virtual ~stack_t();

            stack_t<Value>& operator=(const stack_t<Value>& rhs);
            stack_t<Value>& operator=(stack_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------
            
            bool empty();
            
            void push(Value item);
            template<class... Args> void push(Value item, Args... rest);
            
            Value peek();
            
            Value pop();
    };
    
    
    // -----------
    // MANDATORY
    // -----------

    template<class T>
    stack_t<T>::stack_t() {
        _elements = new singly_linked_list_t<T>();
    }
    
    template<class T>
    stack_t<T>::stack_t(const stack_t<T>& rhs) {
        _elements = new singly_linked_list_t<T>(*(rhs._elements));
    }
    
    template<class T>
    stack_t<T>::stack_t(stack_t<T>&& rhs) {
        _elements = rhs._elements;
        rhs._elements = nullptr;
    }

    template<typename Value>
    stack_t<Value>::~stack_t() {
        delete _elements;
    }

    template<class T>
    stack_t<T>& stack_t<T>::operator=(const stack_t<T>& rhs) {
        delete _elements;
        _elements = new singly_linked_list_t<T>(*(rhs._elements));
    }
    
    template<class T>
    stack_t<T>& stack_t<T>::operator=(stack_t<T>&& rhs) {
        delete _elements;
        
        _elements = rhs._elements;
        rhs._elements = nullptr;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class T>
    bool stack_t<T>::empty() {
        return _elements->length == 0;
    }
    
    template<class T>
    void stack_t<T>::push(T item) {
       _elements->insert(0, item); 
    }
    
    template<class T>
    template<class... Args>
    void stack_t<T>::push(T item, Args... rest) {
        push(item);
        push(rest...);
    }
    
    
    template<class T>
    T stack_t<T>::peek() {
        return _elements[0];
    }
    
    template<class T>
    T stack_t<T>::pop() {
        return _elements->pop(0);
    }
}

#endif
