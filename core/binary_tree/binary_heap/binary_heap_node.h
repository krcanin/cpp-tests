#ifndef BINARY_HEAP_NODE_H
#define BINARY_HEAP_NODE_H

namespace mylib {
    template<typename Key, typename Value>
    class binary_heap_node_t {
        public:
            Key key;
            Value value;

            binary_heap_node_t(Key key, Value value);
            binary_heap_node_t(const binary_heap_node_t<Key, Value>& rhs) = default;
            binary_heap_node_t(binary_heap_node_t<Key, Value>&& rhs) = default;
    };

    template<typename Key, typename Value>
    binary_heap_node_t<Key, Value>::binary_heap_node_t(Key key, Value value) : key(key), value(value) {}
}

#endif
