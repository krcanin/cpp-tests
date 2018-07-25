#ifndef SINGLY_LINKED_LIST_NODE_H
#define SINGLY_LINKED_LIST_NODE_H

namespace mylib {
    template<class Value>
    class singly_linked_list_node_t {
        public:
            singly_linked_list_node_t<Value>* next = nullptr;
            Value value;

            singly_linked_list_node_t(Value value);
            singly_linked_list_node_t(const singly_linked_list_node_t<Value>& rhs) = default;
            singly_linked_list_node_t(singly_linked_list_node_t<Value>&& rhs) = default;
    };
    
    template<class Value>
    singly_linked_list_node_t<Value>::singly_linked_list_node_t(Value value) : value(value) {}
}

#endif
