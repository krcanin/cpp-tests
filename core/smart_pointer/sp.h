#ifndef SP_H
#define SP_H

namespace mylib {
    template<typename PointerType>
    class sp {
        private:
            PointerType* ptr;
            int* rc;
        public:
            sp(PointerType* p);
            sp(const sp& rhs);
            sp(sp&& rhs);

            ~sp();

            PointerType* get();

            PointerType& operator*();
            PointerType* operator->();
    };

    template<typename PointerType>
    sp<PointerType>::sp(PointerType* p) {
        ptr = p;
        rc = new int(1);
    }

    template<typename PointerType>
    sp<PointerType>::sp(const sp<PointerType>& rhs) {
        ptr = rhs.ptr;
        rc = rhs.rc;
        *rc = *rc + 1;
    }

    template<typename PointerType>
    sp<PointerType>::sp(sp<PointerType>&& rhs) {
        ptr = rhs.ptr;
        rhs.ptr = nullptr;

        rc = rhs.rc;
    }

    template<typename PointerType>
    sp<PointerType>::~sp() {
        *rc = *rc - 1;

        if(*rc == 0) {
            delete rc;
            delete ptr;
        }
    }

    template<typename PointerType>
    PointerType* sp<PointerType>::get() {
        return ptr;
    }

    template<typename PointerType>
    PointerType& sp<PointerType>::operator*() {
        return *(operator->());
    }

    template<typename PointerType>
    PointerType* sp<PointerType>::operator->() {
        return ptr;
    }
}

#endif
