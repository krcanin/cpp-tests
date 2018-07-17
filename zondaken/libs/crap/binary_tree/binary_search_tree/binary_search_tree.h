#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <cstdint>
#include <functional>

#include "binary_search_tree_node.h"
#include "binary_search_tree_iterator.h"
#include "binary_search_tree_reverse_iterator.h"

namespace crap {
	// -----------
	// NOTES
	// -----------
	// - iterator constructs a NEW list with copies of all key-value-pairs depending on the current state
    //   and thus you cannot manipulate the elements by iterator

    template<class Key, class Value>
    class binary_search_tree_t {
        private:
            binary_search_tree_node_t<Key, Value>* _head = nullptr;
            uint32_t _count = 0;
            std::function<int32_t(Key, Key)> _compare;

            binary_search_tree_node_t<Key, Value>* copy(binary_search_tree_node_t<Key, Value>* node) const;

            binary_search_tree_node_t<Key, Value>* dispose(binary_search_tree_node_t<Key, Value>* node);

            binary_search_tree_node_t<Key, Value>* get(binary_search_tree_node_t<Key, Value>* node, Key key) const;

			binary_search_tree_node_t<Key, Value>* insert(binary_search_tree_node_t<Key, Value>* node, Key key, Value value);

			binary_search_tree_node_t<Key, Value>* max(binary_search_tree_node_t<Key, Value>* node) const;

			binary_search_tree_node_t<Key, Value>* min(binary_search_tree_node_t<Key, Value>* node) const;

            binary_search_tree_node_t<Key, Value>* remove(binary_search_tree_node_t<Key, Value>* node, Key key);

            binary_search_tree_node_t<Key, Value>* remove_max(binary_search_tree_node_t<Key, Value>* node);

            binary_search_tree_node_t<Key, Value>* remove_min(binary_search_tree_node_t<Key, Value>* node);
        public:
            const uint32_t& length = _count;

            // -----------
            // MANDATORY
            // -----------

            binary_search_tree_t(const binary_search_tree_t<Key, Value>& rhs);
            binary_search_tree_t(binary_search_tree_t<Key, Value>&& rhs);

            virtual ~binary_search_tree_t();

            binary_search_tree_t<Key, Value>& operator=(const binary_search_tree_t<Key, Value>& rhs);
            binary_search_tree_t<Key, Value>& operator=(binary_search_tree_t<Key, Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            binary_search_tree_t(std::function<int32_t(Key, Key)> compare = [](Key x, Key y) { return x - y; });

            binary_search_tree_iterator_t<Key, Value> begin() const;
            binary_search_tree_iterator_t<Key, Value> end() const;
            binary_search_tree_reverse_iterator_t<Key, Value> rbegin() const;
            binary_search_tree_reverse_iterator_t<Key, Value> rend() const;

            void change_key(Key old_key, Key new_key);
            void clear();
            Value& get(Key key) const;
            void insert(Key key, Value value);
            std::pair<Key, Value> max() const;
            std::pair<Key, Value> min() const;
            void remove(Key key);
            void remove_max();
            void remove_min();
            bool search(Key key) const;
            void update(Key key, Value value);
    };

    // -----------
    // PRIVATE
    // -----------

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::copy(binary_search_tree_node_t<Key, Value>* node) const {
        if(node) {
            binary_search_tree_node_t<Key, Value>* result = new binary_search_tree_node_t<Key, Value>(node->key, node->value);
            result->left = copy(node->left);
            result->right = copy(node->right);
            return result;
        } else {
            return node;
        }
    }

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::dispose(binary_search_tree_node_t<Key, Value>* node) {
        if(node) {
            dispose(node->left);
            dispose(node->right);
            delete node;
        }

        return nullptr;
    }

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::get(binary_search_tree_node_t<Key, Value>* node, Key key) const {
        if (node) {
            int cmp_r = _compare(key, node->key);

            if (cmp_r == 0) {
                return node;
            } else if (cmp_r < 0) {
                return get(node->left, key);
            } else {
                return get(node->right, key);
            }
        } else {
            return nullptr;
        }
    }

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::insert(binary_search_tree_node_t<Key, Value>* node, Key key, Value value) {
        if (node) {
            int cmp_r = _compare(key, node->key);

            if (cmp_r < 0) {
                node->left = insert(node->left, key, value);
            } else if (cmp_r > 0) {
                node->right = insert(node->right, key, value);
            } else {
                throw "Key already exists";
            }

            return node;
        } else {
            return new binary_search_tree_node_t<Key, Value>(key, value);
        }
    }

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::max(binary_search_tree_node_t<Key, Value>* node) const {
        if(node) {
            if(node->right) {
                return max(node->right);
            } else {
                return node;
            }
        } else {
            return nullptr;
        }
    }

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::min(binary_search_tree_node_t<Key, Value>* node) const {
        if(node) {
            if(node->left) {
                return max(node->left);
            } else {
                return node;
            }
        } else {
            return nullptr;
        }
    }

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::remove(binary_search_tree_node_t<Key, Value>* node, Key key) {
        if (node) {
            int x = _compare(key, node->key);

            if (x < 0) {
                node->left = remove(node->left, key);
                return node;
            } else if (x > 0) {
                node->right = remove(node->right, key);
                return node;
            } else {
                /* woohoo, right key found! */
                if (!node->left) {
                    /* 0 or 1 child - right */
                    binary_search_tree_node_t<Key, Value>* result = node->right;
                    delete node;
                    return result;
                } else if (!node->right) {
                    /* 1 child - left */
                    binary_search_tree_node_t<Key, Value>* result = node->left;
                    delete node;
                    return result;
                } else {
                    /* 2 children - replace node to be deleted with min node from right subtree and remove min node */
                    binary_search_tree_node_t<Key, Value>* min_node = min(node->right);

                    node->key = min_node->key;
                    node->value = min_node->value;

                    node->right = remove(node->right, min_node->key);

                    return node;
                }
            }
        } else {
            return node;
        }
    }

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::remove_max(binary_search_tree_node_t<Key, Value>* node) {
        if(node) {
            if(node->right) {
                node->right = remove_max(node->right);
                return node;
            } else {
                delete node;
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    template<class Key, class Value>
    binary_search_tree_node_t<Key, Value>* binary_search_tree_t<Key, Value>::remove_min(binary_search_tree_node_t<Key, Value>* node) {
        if(node) {
            if(node->left) {
                node->left = remove_min(node->left);
                return node;
            } else {
                delete node;
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    // -----------
    // MANDATORY
    // -----------

    template<class Key, class Value>
    binary_search_tree_t<Key, Value>::binary_search_tree_t(const binary_search_tree_t<Key, Value>& rhs) {
        _head = copy(rhs._head);
        _count = rhs._count;
        _compare = rhs._compare;
    }

    template<class Key, class Value>
    binary_search_tree_t<Key, Value>::binary_search_tree_t(binary_search_tree_t<Key, Value>&& rhs) {
        _head = rhs._head;
        rhs._head = nullptr;

        _count = rhs._count;
        rhs._count = 0;

        _compare = rhs._compare;
        rhs._compare = nullptr;
    }

    template<class Key, class Value>
    binary_search_tree_t<Key, Value>::~binary_search_tree_t() {
        clear();
    }

    template<class Key, class Value>
    binary_search_tree_t<Key, Value>& binary_search_tree_t<Key, Value>::operator=(const binary_search_tree_t<Key, Value>& rhs) {
        clear();

        _head = copy(rhs._head);
        _count = rhs._count;
        _compare = rhs._compare;
    }

    template<class Key, class Value>
    binary_search_tree_t<Key, Value>& binary_search_tree_t<Key, Value>::operator=(binary_search_tree_t<Key, Value>&& rhs) {
        clear();

        _head = rhs._head;
        rhs._head = nullptr;

        _count = rhs._count;
        rhs._count = 0;

        _compare = rhs._compare;
        rhs._compare = nullptr;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<class Key, class Value>
    binary_search_tree_t<Key, Value>::binary_search_tree_t(std::function<int32_t(Key, Key)> compare) : _compare(compare) {}

    template<class Key, class Value>
    binary_search_tree_iterator_t<Key, Value> binary_search_tree_t<Key, Value>::begin() const {
        return binary_search_tree_iterator_t<Key, Value>(_head, _count);
    }

    template<class Key, class Value>
    binary_search_tree_iterator_t<Key, Value> binary_search_tree_t<Key, Value>::end() const {
    	return binary_search_tree_iterator_t<Key, Value>(nullptr, _count);
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value> binary_search_tree_t<Key, Value>::rbegin() const {
        return binary_search_tree_reverse_iterator_t<Key, Value>(_head, _count);
    }

    template<class Key, class Value>
    binary_search_tree_reverse_iterator_t<Key, Value> binary_search_tree_t<Key, Value>::rend() const {
        return binary_search_tree_reverse_iterator_t<Key, Value>(nullptr, _count);
    }

    template<class Key, class Value>
    void binary_search_tree_t<Key, Value>::change_key(Key old_key, Key new_key) {
        Value value = get(old_key);
        remove(old_key);
        insert(new_key, value);
    }

    template<class Key, class Value>
    void binary_search_tree_t<Key, Value>::clear() {
        _head = dispose(_head);
        _count = 0;
    }

    template<class Key, class Value>
    Value& binary_search_tree_t<Key, Value>::get(Key key) const {
        binary_search_tree_node_t<Key, Value>* node = get(_head, key);

        if(node) {
            return node->value;
        } else {
            throw "Key not found";
        }
    }

    template<class Key, class Value>
    void binary_search_tree_t<Key, Value>::insert(Key key, Value value) {
        _head = insert(_head, key, value);
        _count += 1;
    }

    template<class Key, class Value>
    std::pair<Key, Value> binary_search_tree_t<Key, Value>::max() const {
        if(_count == 0) {
            throw "Empty BST";
        }

        binary_search_tree_node_t<Key, Value>* node = max(_head);
        return std::make_pair(node->key, node->value);
    }

    template<class Key, class Value>
    std::pair<Key, Value> binary_search_tree_t<Key, Value>::min() const {
        if(_count == 0) {
            throw "Empty BST";
        }

        binary_search_tree_node_t<Key, Value>* node = min(_head);
        return std::make_pair(node->key, node->value);
    }

    template<class Key, class Value>
    void binary_search_tree_t<Key, Value>::remove(Key key) {
        if(_count == 0) {
            throw "Empty BST";
        }

        _head = remove(_head, key);
        _count -= 1;
    }

    template<class Key, class Value>
    void binary_search_tree_t<Key, Value>::remove_max() {
        if(_count == 0) {
            throw "Empty BST";
        }

        _head = remove_max(_head);
        _count -= 1;
    }

    template<class Key, class Value>
    void binary_search_tree_t<Key, Value>::remove_min() {
        if(_count == 0) {
            throw "Empty BST";
        }

        _head = remove_min(_head);
        _count -= 1;
    }

    template<class Key, class Value>
    bool binary_search_tree_t<Key, Value>::search(Key key) const {
        binary_search_tree_node_t<Key, Value>* node = get(_head, key);

        if(node) {
            return true;
        } else {
            return false;
        }
    }

    template<class Key, class Value>
    void binary_search_tree_t<Key, Value>::update(Key key, Value value) {
        binary_search_tree_node_t<Key, Value>* node = get(_head, key);

        if(node) {
            node->value = value;
        } else {
            throw "Key not found";
        }
    }
}

#endif
