#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include <cstdint>

namespace crap {
    template<class Key, class Value>
    class avl_tree_node_t {
        public:
            Key key;
            Value value;
            avl_tree_node_t<Key, Value>* left = nullptr;
            avl_tree_node_t<Key, Value>* right = nullptr;
            uint32_t height = 1;

            avl_tree_node_t(Key key, Value value);
            avl_tree_node_t(const avl_tree_node_t<Key, Value>& rhs) = default;
            avl_tree_node_t(avl_tree_node_t<Key, Value>&& rhs) = default;
    };

    template<class Key, class Value>
    avl_tree_node_t<Key, Value>::avl_tree_node_t(Key key, Value value) : key(key), value(value) {}
}

#endif
