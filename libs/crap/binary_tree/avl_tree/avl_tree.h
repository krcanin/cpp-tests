#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "avl_tree_node.h"
#include "avl_tree_iterator.h"
#include "avl_tree_reverse_iterator.h"

namespace crap {
    template<class Key, class Value>
    class avl_tree_t {
        public:
            avl_tree_node_t<Key, Value>* _head = nullptr;
            uint32_t _count = 0;
            std::function<int(Key, Key)> _compare;

            int32_t balance(avl_tree_node_t<Key, Value>* node) const;

            avl_tree_node_t<Key, Value>* copy(avl_tree_node_t<Key, Value>* node) const;

            avl_tree_node_t<Key, Value>* dispose(avl_tree_node_t<Key, Value>* node);

            avl_tree_node_t<Key, Value>* get(avl_tree_node_t<Key, Value>* node, Key key) const;

            int32_t get_height(avl_tree_node_t<Key, Value>* node) const;

            avl_tree_node_t<Key, Value>* insert(avl_tree_node_t<Key, Value>* node, Key key, Value value);

            avl_tree_node_t<Key, Value>* max(avl_tree_node_t<Key, Value>* node) const;

            avl_tree_node_t<Key, Value>* min(avl_tree_node_t<Key, Value>* node) const;

            avl_tree_node_t<Key, Value>* rebalance(avl_tree_node_t<Key, Value>* node);

            avl_tree_node_t<Key, Value>* remove(avl_tree_node_t<Key, Value>* node, Key key);

            avl_tree_node_t<Key, Value>* remove_max(avl_tree_node_t<Key, Value>* node);

            avl_tree_node_t<Key, Value>* remove_min(avl_tree_node_t<Key, Value>* node);

			avl_tree_node_t<Key, Value>* rotate_left(avl_tree_node_t<Key, Value>* head);

			avl_tree_node_t<Key, Value>* rotate_right(avl_tree_node_t<Key, Value>* head);

			avl_tree_node_t<Key, Value>* rotate_left_right(avl_tree_node_t<Key, Value>* head);

			avl_tree_node_t<Key, Value>* rotate_right_left(avl_tree_node_t<Key, Value>* head);
            
            int32_t set_height(avl_tree_node_t<Key, Value>* node) const;
        public:
            const uint32_t& length = _count;

            // -----------
            // MANDATORY
            // -----------

            avl_tree_t(const avl_tree_t<Key, Value>& rhs);
            avl_tree_t(avl_tree_t<Key, Value>&& rhs);

            virtual ~avl_tree_t();

            avl_tree_t<Key, Value>& operator=(const avl_tree_t<Key, Value>& rhs);
            avl_tree_t<Key, Value>& operator=(avl_tree_t<Key, Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            avl_tree_t(std::function<int(Key, Key)> compare = [](Key x, Key y) { return x - y; });

            avl_tree_iterator_t<Key, Value> begin() const;
            avl_tree_iterator_t<Key, Value> end() const;
            avl_tree_reverse_iterator_t<Key, Value> rbegin() const;
            avl_tree_reverse_iterator_t<Key, Value> rend() const;

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
	int32_t avl_tree_t<Key, Value>::balance(avl_tree_node_t<Key, Value>* head) const {
		if (head) {
			return get_height(head->right) - get_height(head->left);
		} else {
			return 0;
		}
	}

    template<class Key, class Value>
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::copy(avl_tree_node_t<Key, Value>* node) const {
        if(node) {
            avl_tree_node_t<Key, Value>* result = new avl_tree_node_t<Key, Value>(node->key, node->value);
            result->left = copy(node->left);
            result->right = copy(node->right);
            return result;
        } else {
            return node;
        }
    }

    template<class Key, class Value>
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::dispose(avl_tree_node_t<Key, Value>* node) {
        if(node) {
            dispose(node->left);
            dispose(node->right);
            delete node;
        }

        return nullptr;
    }

    template<class Key, class Value>
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::get(avl_tree_node_t<Key, Value>* node, Key key) const {
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
	int32_t avl_tree_t<Key, Value>::get_height(avl_tree_node_t<Key, Value>* node) const {
		if (node) {
			return node->height;
		} else {
			return 0;
		}
	}

    template<class Key, class Value>
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::insert(avl_tree_node_t<Key, Value>* node, Key key, Value value) {
        if (node) {
            int cmp_r = _compare(key, node->key);

            if (cmp_r < 0) {
                node->left = insert(node->left, key, value);
            } else if (cmp_r > 0) {
                node->right = insert(node->right, key, value);
            } else {
                throw "Key already exists";
            }

            node->height = std::max(get_height(node->left), get_height(node->right)) + 1;

            return rebalance(node);
        } else {
            return new avl_tree_node_t<Key, Value>(key, value);
        }
    }

    template<class Key, class Value>
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::max(avl_tree_node_t<Key, Value>* node) const {
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
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::min(avl_tree_node_t<Key, Value>* node) const {
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
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::remove(avl_tree_node_t<Key, Value>* node, Key key) {
        if (node) {
            int x = _compare(key, node->key);

            if (x < 0) {
                node->left = remove(node->left, key);
                return rebalance(node);
            } else if (x > 0) {
                node->right = remove(node->right, key);
                return rebalance(node);
            } else {
                /* woohoo, right key found! */
                if (!node->left) {
                    /* 0 or 1 child - right */
                    avl_tree_node_t<Key, Value>* result = node->right;
                    delete node;
                    if(result) result->height = set_height(result);
                    return rebalance(result);
                } else if (!node->right) {
                    /* 1 child - left */
                    avl_tree_node_t<Key, Value>* result = node->left;
                    delete node;
                    if(result) result->height = set_height(result);
                    return rebalance(result);
                } else {
                    /* 2 children - replace node to be deleted with min node from right subtree and remove min node */
                    avl_tree_node_t<Key, Value>* min_node = min(node->right);

                    node->key = min_node->key;
                    node->value = min_node->value;

                    node->right = remove(node->right, min_node->key);

                    node->height = set_height(node);

                    return rebalance(node);
                }
            }
        } else {
            return node;
        }
    }

    template<class Key, class Value>
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::remove_max(avl_tree_node_t<Key, Value>* node) {
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
    avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::remove_min(avl_tree_node_t<Key, Value>* node) {
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

	template<class Key, class Value>
	avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::rebalance(avl_tree_node_t<Key, Value>* node) {
		if (node) {
			switch (balance(node)) {
    			case 2:
    				switch (balance(node->right)) {
                        case 1:
                            node = rotate_left(node);
                            break;
                        case -1:
                            node = rotate_right_left(node);
                            break;
    				}

    				break;
    			case -2:
    				switch (balance(node->left)) {
                        case 1:
                            node = rotate_left_right(node);
                            break;
                        case -1:
                            node = rotate_right(node);
                            break;
    				}

    				break;
			}

			return node;
		} else {
			return node;
		}
	}

	template<class Key, class Value>
	avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::rotate_left(avl_tree_node_t<Key, Value>* node) {
		avl_tree_node_t<Key, Value>* result = node->right;
		node->right = result->left;
		result->left = node;

		result->height = set_height(result);
		result->left->height = set_height(result->left);

		return result;
	}

	template<class Key, class Value>
	avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::rotate_right(avl_tree_node_t<Key, Value>* head) {
		avl_tree_node_t<Key, Value>* result = head->left;
		head->left = result->right;
		result->right = head;

		result->height = set_height(result);
		result->right->height = set_height(result->right);

		return result;
	}

	template<class Key, class Value>
	avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::rotate_left_right(avl_tree_node_t<Key, Value>* head) {
		head->left = rotate_left(head->left);
		return rotate_right(head);
	}

	template<class Key, class Value>
	avl_tree_node_t<Key, Value>* avl_tree_t<Key, Value>::rotate_right_left(avl_tree_node_t<Key, Value>* head) {
		head->right = rotate_right(head->right);

		return rotate_left(head);
	}

    template<class Key, class Value>
	int32_t avl_tree_t<Key, Value>::set_height(avl_tree_node_t<Key, Value>* node) const {
		if (node) {
			return 1 + std::max(set_height(node->left), set_height(node->right));
		} else {
			return 0;
		}
	}

    // -----------
    // MANDATORY
    // -----------

    template<class Key, class Value>
    avl_tree_t<Key, Value>::avl_tree_t(const avl_tree_t<Key, Value>& rhs) {
        _head = copy(rhs._head);
        _count = rhs._count;
        _compare = rhs._compare;
    }

    template<class Key, class Value>
    avl_tree_t<Key, Value>::avl_tree_t(avl_tree_t<Key, Value>&& rhs) {
        _head = rhs._head;
        rhs._head = nullptr;

        _count = rhs._count;
        rhs._count = 0;

        _compare = rhs._compare;
        rhs._compare = nullptr;
    }

    template<class Key, class Value>
    avl_tree_t<Key, Value>::~avl_tree_t() {
        clear();
    }

    template<class Key, class Value>
    avl_tree_t<Key, Value>& avl_tree_t<Key, Value>::operator=(const avl_tree_t<Key, Value>& rhs) {
        clear();

        _head = copy(rhs._head);
        _count = rhs._count;
        _compare = rhs._compare;
    }

    template<class Key, class Value>
    avl_tree_t<Key, Value>& avl_tree_t<Key, Value>::operator=(avl_tree_t<Key, Value>&& rhs) {
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
    avl_tree_t<Key, Value>::avl_tree_t(std::function<int(Key, Key)> compare) : _compare(compare) {}

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value> avl_tree_t<Key, Value>::begin() const {
        return avl_tree_iterator_t<Key, Value>(_head, 0);
    }

    template<class Key, class Value>
    avl_tree_iterator_t<Key, Value> avl_tree_t<Key, Value>::end() const {
    	return avl_tree_iterator_t<Key, Value>(_head, _count);
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value> avl_tree_t<Key, Value>::rbegin() const {
        return avl_tree_reverse_iterator_t<Key, Value>(_head, 0);
    }

    template<class Key, class Value>
    avl_tree_reverse_iterator_t<Key, Value> avl_tree_t<Key, Value>::rend() const {
        return avl_tree_reverse_iterator_t<Key, Value>(nullptr, _count);
    }

    template<class Key, class Value>
    void avl_tree_t<Key, Value>::change_key(Key old_key, Key new_key) {
        Value value = get(old_key);
        remove(old_key);
        insert(new_key, value);
    }

    template<class Key, class Value>
    void avl_tree_t<Key, Value>::clear() {
        _head = dispose(_head);
        _count = 0;
    }

    template<class Key, class Value>
    Value& avl_tree_t<Key, Value>::get(Key key) const {
        avl_tree_node_t<Key, Value>* node = get(_head, key);

        if(node) {
            return node->value;
        } else {
            throw "Key not found";
        }
    }

    template<class Key, class Value>
    void avl_tree_t<Key, Value>::insert(Key key, Value value) {
        _head = insert(_head, key, value);
        _count += 1;
    }

    template<class Key, class Value>
    std::pair<Key, Value> avl_tree_t<Key, Value>::max() const {
        if(_count == 0) {
            throw "Empty BST";
        }

        avl_tree_node_t<Key, Value>* node = max(_head);
        return std::make_pair(node->key, node->value);
    }

    template<class Key, class Value>
    std::pair<Key, Value> avl_tree_t<Key, Value>::min() const {
        if(_count == 0) {
            throw "Empty BST";
        }

        avl_tree_node_t<Key, Value>* node = min(_head);
        return std::make_pair(node->key, node->value);
    }

    template<class Key, class Value>
    void avl_tree_t<Key, Value>::remove(Key key) {
        if(_count == 0) {
            throw "Empty BST";
        }

        _head = remove(_head, key);
        _count -= 1;
    }

    template<class Key, class Value>
    void avl_tree_t<Key, Value>::remove_max() {
        if(_count == 0) {
            throw "Empty BST";
        }

        _head = remove_max(_head);
        _count -= 1;
    }

    template<class Key, class Value>
    void avl_tree_t<Key, Value>::remove_min() {
        if(_count == 0) {
            throw "Empty BST";
        }

        _head = remove_min(_head);
        _count -= 1;
    }

    template<class Key, class Value>
    bool avl_tree_t<Key, Value>::search(Key key) const {
        avl_tree_node_t<Key, Value>* node = get(_head, key);

        if(node) {
            return true;
        } else {
            return false;
        }
    }

    template<class Key, class Value>
    void avl_tree_t<Key, Value>::update(Key key, Value value) {
        avl_tree_node_t<Key, Value>* node = get(_head, key);

        if(node) {
            node->value = value;
        } else {
            throw "Key not found";
        }
    }
}

#endif
