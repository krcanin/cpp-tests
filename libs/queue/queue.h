#ifndef QUEUE_H
#define QUEUE_H

namespace mylib {
    template<class Value>
    class queue_t {
        private:
            singly_linked_list_t<Value>* _elements;
        public:
            // -----------
            // MANDATORY
            // -----------

            queue_t();
            queue_t(const queue_t<Value>& rhs);
            queue_t(queue_t<Value>&& rhs);

            virtual ~queue_t();

            queue_t<Value>& operator=(const queue_t<Value>& rhs);
            queue_t<Value>& operator=(queue_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------
            
            bool empty();
            
            void enqueue(Value item);
            template<class... Args> void enqueue(Value item, Args... rest);
            
            Value peek();
            
            Value dequeue();
    };
    
    
    // -----------
    // MANDATORY
    // -----------

    template<class T>
    queue_t<T>::queue_t() {
        _elements = new singly_linked_list_t<T>();
    }
    
    template<class T>
    queue_t<T>::queue_t(const queue_t<T>& rhs) {
        _elements = new singly_linked_list_t<T>(*(rhs._elements));
    }
    
    template<class T>
    queue_t<T>::queue_t(queue_t<T>&& rhs) {
        _elements = rhs._elements;
        rhs._elements = nullptr;
    }

    template<class Value>
    queue_t<Value>::~queue_t() {
        delete _elements;
    }

    template<class T>
    queue_t<T>& queue_t<T>::operator=(const queue_t<T>& rhs) {
        delete _elements;
        _elements = new singly_linked_list_t<T>(*(rhs._elements));
    }
    
    template<class T>
    queue_t<T>& queue_t<T>::operator=(queue_t<T>&& rhs) {
        delete _elements;
        
        _elements = rhs._elements;
        rhs._elements = nullptr;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class T>
    bool queue_t<T>::empty() {
        return _elements->length == 0;
    }
    
    template<class T>
    void queue_t<T>::enqueue(T item) {
       _elements->append(item); 
    }
    
    template<class T>
    template<class... Args>
    void queue_t<T>::enqueue(T item, Args... rest) {
        enqueue(item);
        enqueue(rest...);
    }
    
    template<class T>
    T queue_t<T>::peek() {
        return _elements[0];
    }
    
    template<class T>
    T queue_t<T>::dequeue() {
        return _elements->pop(0);
    }
}

#endif
