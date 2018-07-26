#ifndef QUEUE_H
#define QUEUE_H

namespace mylib {
    template<typename Value>
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
            template<typename... Args> void enqueue(Value item, Args... rest);
            
            Value peek();
            
            Value dequeue();
    };
    
    
    // -----------
    // MANDATORY
    // -----------

    template<typename T>
    queue_t<T>::queue_t() {
        _elements = new singly_linked_list_t<T>();
    }
    
    template<typename T>
    queue_t<T>::queue_t(const queue_t<T>& rhs) {
        _elements = new singly_linked_list_t<T>(*(rhs._elements));
    }
    
    template<typename T>
    queue_t<T>::queue_t(queue_t<T>&& rhs) {
        _elements = rhs._elements;
        rhs._elements = nullptr;
    }

    template<typename Value>
    queue_t<Value>::~queue_t() {
        delete _elements;
    }

    template<typename T>
    queue_t<T>& queue_t<T>::operator=(const queue_t<T>& rhs) {
        delete _elements;
        _elements = new singly_linked_list_t<T>(*(rhs._elements));
    }
    
    template<typename T>
    queue_t<T>& queue_t<T>::operator=(queue_t<T>&& rhs) {
        delete _elements;
        
        _elements = rhs._elements;
        rhs._elements = nullptr;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<typename T>
    bool queue_t<T>::empty() {
        return _elements->length == 0;
    }
    
    template<typename T>
    void queue_t<T>::enqueue(T item) {
       _elements->append(item); 
    }
    
    template<typename T>
    template<typename... Args>
    void queue_t<T>::enqueue(T item, Args... rest) {
        enqueue(item);
        enqueue(rest...);
    }
    
    template<typename T>
    T queue_t<T>::peek() {
        return _elements[0];
    }
    
    template<typename T>
    T queue_t<T>::dequeue() {
        return _elements->pop(0);
    }
}

#endif
