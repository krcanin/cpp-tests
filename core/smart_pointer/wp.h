#ifndef WP_H
#define WP_H

#include "sp.h"

namespace mylib {
    template<typename PointerType>
    class wp {
        private:
            PointerType* ptr;
        public:
            wp();
            wp(const sp<PointerType>& p);
            wp(const wp<PointerType>& rhs);
            wp(wp<PointerType>&& rhs);

            ~wp();

            operator PointerType*();

            PointerType& operator*();
            PointerType* operator->();

            wp<PointerType>& operator=(const sp<PointerType>& rhs);
            wp<PointerType>& operator=(const wp<PointerType>& rhs);
            wp<PointerType>& operator=(wp<PointerType>&& rhs);
    };

    template<typename PointerType>
    wp<PointerType>::wp() {
        ptr = nullptr;
    }

    template<typename PointerType>
    wp<PointerType>::wp(PointerType* p) {
        ptr = p;
    }

    template<typename PointerType>
    wp<PointerType>::wp(const wp<PointerType>& rhs) {
        ptr = rhs.ptr;
    }

    template<typename PointerType>
    wp<PointerType>::wp(wp<PointerType>&& rhs) {
        ptr = rhs.ptr;
        rhs.ptr = nullptr;
    }

    template<typename PointerType>
    wp<PointerType>::~wp() {}

    template<typename PointerType>
    wp<PointerType>::operator PointerType*() {
        return ptr;
    }

    template<typename PointerType>
    PointerType& wp<PointerType>::operator*() {
        return *(operator->());
    }

    template<typename PointerType>
    PointerType* wp<PointerType>::operator->() {
        return ptr;
    }

    template<typename PointerType>
    wp<PointerType>& wp<PointerType>::operator=(PointerType* rhs) {
        this->~wp();

        if(rhs) {
            ptr = rhs;
        } else {
            ptr = nullptr;
        }
    }

    template<typename PointerType>
    wp<PointerType>& wp<PointerType>::operator=(const wp<PointerType>& rhs) {
        this->~wp();

        ptr = rhs.ptr;
    }

    template<typename PointerType>
    wp<PointerType>& wp<PointerType>::operator=(wp<PointerType>&& rhs) {
        this->~wp();

        ptr = rhs.ptr;
        rhs.ptr = nullptr;
    }
}

#endif
