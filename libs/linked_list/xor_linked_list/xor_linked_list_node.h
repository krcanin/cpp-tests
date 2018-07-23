#ifndef XOR_LINKED_LIST_NODE_H
#define XOR_LINKED_LIST_NODE_H

namespace crap {
    template<class Value>
    class xor_linked_list_node_t {
        public:
            Value value;
            xor_linked_list_node_t<Value>* npx = nullptr;

            xor_linked_list_node_t(Value value);
            xor_linked_list_node_t(const xor_linked_list_node_t<Value>& rhs) = default;
            xor_linked_list_node_t(xor_linked_list_node_t<Value>&& rhs) = default;
    };
    
    template<class Value>
    xor_linked_list_node_t<Value>::xor_linked_list_node_t(Value value) : value(value) {}
}

#endif
