#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <cstdint>
#include <initializer_list>
#include <functional>
#include <stdexcept>

#include "singly_linked_list_node.h"
#include "singly_linked_list_iterator.h"

namespace mylib {
    template<typename Value>
    class singly_linked_list_t {
        private:
            singly_linked_list_node_t<Value>* _head = nullptr;
            singly_linked_list_node_t<Value>* _rear = nullptr;
            uint32_t _count = 0;

            singly_linked_list_node_t<Value>* get_node(uint32_t index) const;

            template<typename U> void merge_sort(singly_linked_list_node_t<Value>** head, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse);

            template<typename U> singly_linked_list_node_t<Value>* merge(singly_linked_list_node_t<Value>* first, singly_linked_list_node_t<Value>* second, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse);

            void split(singly_linked_list_node_t<Value>* head, singly_linked_list_node_t<Value>** front, singly_linked_list_node_t<Value>** back) const;
        public:
            const uint32_t& length = _count;

            // -----------
            // MANDATORY
            // -----------

            singly_linked_list_t();
            singly_linked_list_t(const singly_linked_list_t<Value>& rhs);
            singly_linked_list_t(singly_linked_list_t<Value>&& rhs);

            virtual ~singly_linked_list_t();

            singly_linked_list_t<Value>& operator=(const singly_linked_list_t<Value>& rhs);
            singly_linked_list_t<Value>& operator=(singly_linked_list_t<Value>&& rhs);

            // -----------
            // USER-DEFINED
            // -----------

            void append(Value item);
            template<typename... Args> void append(Value item, Args... rest);

            singly_linked_list_iterator_t<Value> begin() const;

            void clear();

            singly_linked_list_t<Value>* copy() const;

            uint32_t count(Value item) const;

            singly_linked_list_iterator_t<Value> end() const;

            template<typename Iterator> void extend(Iterator it);
            void extend(std::initializer_list<Value> elements);
            void extend(Value* arr, uint32_t l, uint32_t r);
            void extend(Value* arr, uint32_t n);

            uint32_t index(Value item, uint32_t start, uint32_t end) const;
            uint32_t index(Value item, uint32_t start) const;
            uint32_t index(Value item) const;

            void insert(uint32_t index, Value item);

            template<typename U> bool is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) const;
            template<typename U> bool is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key) const;
            bool is_sorted(std::function<int32_t(Value, Value)> cmp) const;
            bool is_sorted() const;

            Value pop(uint32_t index);
            Value pop();

            void remove(Value item);

            void reverse();

            template<typename U> void sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key, bool reverse);
            template<typename U> void sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key);
            void sort(std::function<int32_t(Value, Value)> cmp);
            void sort();

            singly_linked_list_t<Value>* sublist(uint32_t left, uint32_t right, uint32_t step) const;

            Value& operator[](uint32_t index) const;

            template<typename Iterator> singly_linked_list_t<Value>* operator+(Iterator rhs) const;
            singly_linked_list_t<Value>* operator+(const singly_linked_list_t<Value>& rhs) const;

            template<typename Iterator> singly_linked_list_t<Value>& operator+=(Iterator rhs);
            singly_linked_list_t<Value>& operator+=(const singly_linked_list_t<Value>& rhs);

            singly_linked_list_t<Value>* operator*(uint32_t amount) const;
    };

    // -----------
    // PRIVATE
    // -----------

    template<typename Value>
    singly_linked_list_node_t<Value>* singly_linked_list_t<Value>::get_node(uint32_t index) const {
        if(index >= _count) {
            throw std::runtime_error("Index out of range");
        }

        singly_linked_list_node_t<Value>* current = _head;
        uint32_t i = 0;

        while(i < index) {
            current = current->next;
            i += 1;
        }

        return current;
    }

    template<typename Value>
    template<typename U>
    void singly_linked_list_t<Value>::merge_sort(singly_linked_list_node_t<Value>** head, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) {
        if(*head && (*head)->next) {
            singly_linked_list_node_t<Value> *first, *last;
            split(*head, &first, &last);

            merge_sort(&first, cmp, key, reverse);
            merge_sort(&last, cmp, key, reverse);

            *head = merge(first, last, cmp, key, reverse);
        }
    }

    template<typename Value>
    template<typename U>
    singly_linked_list_node_t<Value>* singly_linked_list_t<Value>::merge(singly_linked_list_node_t<Value>* first, singly_linked_list_node_t<Value>* second, std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) {
        singly_linked_list_node_t<Value>* result;

        if(!first) {
            return second;
        } else if(!second) {
            return first;
        } else {
            int cmp_r = cmp(key(first->value), key(second->value));
            cmp_r = reverse ? -cmp_r : cmp_r;

            if(cmp_r <= 0) {
                result = first;
                result->next = merge(first->next, second, cmp, key, reverse);
            } else {
                result = second;
                result->next = merge(first, second->next, cmp, key, reverse);
            }

            return result;
        }
    }

    template<typename Value>
    void singly_linked_list_t<Value>::split(singly_linked_list_node_t<Value>* head, singly_linked_list_node_t<Value>** front, singly_linked_list_node_t<Value>** back) const {
        singly_linked_list_node_t<Value>* slow = head;
        singly_linked_list_node_t<Value>* fast = head->next;

        while(fast) {
            fast = fast->next;

            if(fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = head;
        *back = slow->next;
        slow->next = NULL;
    }

    // -----------
    // MANDATORY
    // -----------

    template<typename Value>
    singly_linked_list_t<Value>::singly_linked_list_t() {}

    template<typename Value>
    singly_linked_list_t<Value>::singly_linked_list_t(const singly_linked_list_t<Value>& rhs) {
        for(Value item : rhs) {
            append(item);
        }
    }

    template<typename Value>
    singly_linked_list_t<Value>::singly_linked_list_t(singly_linked_list_t<Value>&& rhs) {
        _head = rhs._head;
        rhs._head = nullptr;

        _rear = rhs._rear;
        rhs._head = nullptr;

        _count = rhs._count;
        rhs._count = 0;
    }

    template<typename Value>
    singly_linked_list_t<Value>::~singly_linked_list_t() {
        clear();
    }

    template<typename Value>
    singly_linked_list_t<Value>& singly_linked_list_t<Value>::operator=(const singly_linked_list_t<Value>& rhs) {
        clear();

        for(Value item : rhs) {
            append(item);
        }
    }

    template<typename Value>
    singly_linked_list_t<Value>& singly_linked_list_t<Value>::operator=(singly_linked_list_t<Value>&& rhs) {
        clear();

        _head = rhs._head;
        rhs._head = nullptr;

        _rear = rhs._rear;
        rhs._head = nullptr;

        _count = rhs._count;
        rhs._count = 0;
    }

    // -----------
    // USER-DEFINED
    // -----------

    template<typename Value>
    void singly_linked_list_t<Value>::append(Value item) {
        singly_linked_list_node_t<Value>* node = new singly_linked_list_node_t<Value>(item);

        if(_count > 0) {
            _rear->next = node;
            _rear = node;
        } else {
            _head = _rear = node;
        }

        _count += 1;
    }

    template<typename Value>
    template<typename... Args>
    void singly_linked_list_t<Value>::append(Value item, Args... rest) {
        append(item);
        append(rest...);
    }

    template<typename Value>
    singly_linked_list_iterator_t<Value> singly_linked_list_t<Value>::begin() const {
        return singly_linked_list_iterator_t<Value>(_head);
    }

    template<typename Value>
    void singly_linked_list_t<Value>::clear() {
        singly_linked_list_node_t<Value> *current, *next;

        current = _head;

        while(current) {
            next = current->next;
            delete current;
            current = next;
        }

        _head = _rear = nullptr;
        _count = 0;
    }

    template<typename Value>
    singly_linked_list_t<Value>* singly_linked_list_t<Value>::copy() const {
        return new singly_linked_list_t<Value>(*this);
    }

    template<typename Value>
    uint32_t singly_linked_list_t<Value>::count(Value item) const {
        uint32_t result = 0;

        for(Value current : *this) {
            if(current == item) {
                result += 1;
            }
        }

        return result;
    }

    template<typename Value>
    singly_linked_list_iterator_t<Value> singly_linked_list_t<Value>::end() const {
        return singly_linked_list_iterator_t<Value>(nullptr);
    }

    template<typename Value>
    template<typename Iterator>
    void singly_linked_list_t<Value>::extend(Iterator it) {
        for(Value item : it) {
            append(item);
        }
    }

    template<typename Value>
    void singly_linked_list_t<Value>::extend(std::initializer_list<Value> elements) {
        for(Value item : elements) {
            append(item);
        }
    }

    template<typename Value>
    void singly_linked_list_t<Value>::extend(Value* arr, uint32_t l, uint32_t r){
        for(uint32_t i = l; i < r; i += 1) {
            append(arr[i]);
        }
    }

    template<typename Value>
    void singly_linked_list_t<Value>::extend(Value* arr, uint32_t n){
        extend(arr, 0, n);
    }

    template<typename Value>
    uint32_t singly_linked_list_t<Value>::index(Value item, uint32_t start, uint32_t end) const {
        uint32_t i = 0;

        for(Value current : *this) {
            if(current == item) {
                return i;
            }

            i += 1;
        }

        throw std::runtime_error("Item not found");
    }

    template<typename Value>
    uint32_t singly_linked_list_t<Value>::index(Value item, uint32_t start) const {
        return index(item, start, _count);
    }

    template<typename Value>
    uint32_t singly_linked_list_t<Value>::index(Value item) const {
        return index(item, 0, _count);
    }

    template<typename Value>
    void singly_linked_list_t<Value>::insert(uint32_t index, Value item) {
        singly_linked_list_node_t<Value>* node = new singly_linked_list_node_t<Value>(item);

        if(index > 0) {
            singly_linked_list_node_t<Value>* prev = get_node(index - 1);

            node->next = prev->next;
            prev->next = node;
        } else {
            node->next = _head;
            _head = node;
        }

        if(index == _count) {
            _rear = node;
        }

        _count += 1;
    }

    template<typename Value>
    template<typename U>
    bool singly_linked_list_t<Value>::is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key, bool reverse) const {
        if(_count <= 1) {
            return true;
        } else {
            auto it = begin();
            Value current = *it;
            it += 1;

            while(it != end()) {
                int cmp_r = cmp(key(*it), key(current));
                cmp_r = reverse ? -cmp_r : cmp_r;

                if (cmp_r < 0) {
                    return false;
                }

                current = *it;
                it += 1;
            }
        }
    }

    template<typename Value>
    template<typename U>
    bool singly_linked_list_t<Value>::is_sorted(std::function<int32_t(U, U)> cmp, std::function<U(Value)> key) const {
        return is_sorted(cmp, key, false);
    }

    template<typename Value>
    bool singly_linked_list_t<Value>::is_sorted(std::function<int32_t(Value, Value)> cmp) const {
        return is_sorted<Value>(cmp, [](Value x) { return x; }, false);
    }

    template<typename Value>
    bool singly_linked_list_t<Value>::is_sorted() const {
        return is_sorted<Value>([](Value x, Value y) { return x - y; }, [](Value x) { return x; }, false);
    }

    template<typename Value>
    Value singly_linked_list_t<Value>::pop(uint32_t index) {
        if(index >= _count) {
            throw std::runtime_error("Index out of range");
        }

        _count -= 1;

        if(index == 0) {
            Value result = _head->value;

            singly_linked_list_node_t<Value>* next = _head->next;
            delete _head;
            _head = next;

            return result;
        } else {
            singly_linked_list_node_t<Value>* prev = get_node(index - 1);
            singly_linked_list_node_t<Value>* current = prev->next;
            singly_linked_list_node_t<Value>* next = current->next;

            Value result = current->value;

            delete current;
            prev->next = next;

            if(index == (_count - 1)) {
                _rear = prev;
            }

            return result;
        }
    }

    template<typename Value>
    Value singly_linked_list_t<Value>::pop() {
        return pop(_count - 1);
    }

    template<typename Value>
    void singly_linked_list_t<Value>::remove(Value item) {
        pop(index(item));
    }

    template<typename Value>
    void singly_linked_list_t<Value>::reverse() {
        if(_count > 1) {
            singly_linked_list_node_t<Value> *prev, *current, *next;

            prev = nullptr;
            current = _head;
            next = _head->next;

            while(current) {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }

            std::swap(_head, _rear);
        }
    }

    template<typename Value>
    template<typename U>
    void singly_linked_list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key, bool reverse) {
        // https://www.cdn.geeksforgeeks.org/merge-sort-for-linked-list/
        merge_sort<U>(&_head, cmp, key, reverse);
    }

    template<typename Value>
    template<typename U>
    void singly_linked_list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp, std::function<U(Value)> key) {
        sort(cmp, key, false);
    }

    template<typename Value>
    void singly_linked_list_t<Value>::sort(std::function<int32_t(Value, Value)> cmp) {
        sort<Value>(cmp, [](Value x) { return x; }, false);
    }

    template<typename Value>
    void singly_linked_list_t<Value>::sort() {
        sort<Value>([](Value x, Value y) { return x - y; }, [](Value x) { return x; }, false);
    }

    template<typename Value>
    singly_linked_list_t<Value>* singly_linked_list_t<Value>::sublist(uint32_t left, uint32_t right, uint32_t step) const {
        if(left >= _count) {
            throw std::runtime_error("Invalid left index");
        } else if(right >= _count) {
            throw std::runtime_error("Invalid right index");
        } else {
            singly_linked_list_t<Value>* result = new singly_linked_list_t<Value>();

            singly_linked_list_node_t<Value>* node = get_node(left);
            uint32_t i = left;

            while(i < right) {
                result->append(node->value);

                for(uint32_t j = 0; j < step; j += 1) {
                    node = node->next;
                }

                i += step;
            }

            return result;
        }
    }

    template<typename Value>
    Value& singly_linked_list_t<Value>::operator[](uint32_t index) const {
        singly_linked_list_node_t<Value>* node = get_node(index);
        return node->value;
    }

    template<typename Value>
    template<typename Iterator>
    singly_linked_list_t<Value>* singly_linked_list_t<Value>::operator+(Iterator rhs) const {
        singly_linked_list_t<Value>* result = new singly_linked_list_t<Value>(*this);

        for(Value item : rhs) {
            result->append(item);
        }

        return result;
    }

    template<typename Value>
    singly_linked_list_t<Value>* singly_linked_list_t<Value>::operator+(const singly_linked_list_t<Value>& rhs) const {
        singly_linked_list_t<Value>* result = new singly_linked_list_t<Value>(*this);

        for(Value item : rhs) {
            result->append(item);
        }

        return result;
    }

    template<typename Value>
    template<typename Iterator>
    singly_linked_list_t<Value>& singly_linked_list_t<Value>::operator+=(Iterator rhs) {
        for(Value item : rhs) {
            append(item);
        }

        return *this;
    }

    template<typename Value>
    singly_linked_list_t<Value>& singly_linked_list_t<Value>::operator+=(const singly_linked_list_t<Value>& rhs) {
        for(Value item : rhs) {
            append(item);
        }

        return *this;
    }

    template<typename Value>
    singly_linked_list_t<Value>* singly_linked_list_t<Value>::operator*(uint32_t amount) const {
        singly_linked_list_t<Value>* result = new singly_linked_list_t<Value>();

        for(uint32_t i = 0; i < amount; i += 1) {
            for(Value item : *this) {
                result->append(item);
            }
        }

        return result;
    }
}

#endif
