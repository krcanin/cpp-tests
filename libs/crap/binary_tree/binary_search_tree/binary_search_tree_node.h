#ifndef BINARY_SEARCH_TREE_NODE_H
#define BINARY_SEARCH_TREE_NODE_H

namespace crap {
    template<class Key, class Value>
    class binary_search_tree_node_t {
        public:
            Key key;
            Value value;
            binary_search_tree_node_t<Key, Value>* left = nullptr;
            binary_search_tree_node_t<Key, Value>* right = nullptr;

            binary_search_tree_node_t(Key key, Value value);
            binary_search_tree_node_t(const binary_search_tree_node_t<Key, Value>& rhs) = default;
            binary_search_tree_node_t(binary_search_tree_node_t<Key, Value>&& rhs) = default;
    };
    
    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>::binary_search_tree_node_t(Key key, Value value) : key(key), value(value) {}
}

#endif
