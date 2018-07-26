#ifndef DOUBLY_LINKED_LIST_NODE_H
#define DOUBLY_LINKED_LIST_NODE_H

namespace mylib {
    template<typename Value>
    class doubly_linked_list_node_t {
        public:
            doubly_linked_list_node_t<Value>* next = nullptr;
            doubly_linked_list_node_t<Value>* prev = nullptr;
            Value value;

            doubly_linked_list_node_t(Value value);
            doubly_linked_list_node_t(const doubly_linked_list_node_t<Value>& rhs) = default;
            doubly_linked_list_node_t(doubly_linked_list_node_t<Value>&& rhs) = default;
    };
    
    template<typename Value>
    doubly_linked_list_node_t<Value>::doubly_linked_list_node_t(Value value) : value(value) {}
}

#endif
