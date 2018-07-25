#ifndef SP_H
#define SP_H

namespace mylib {
    template<class PointerType>
    class sp {
        private:
            PointerType* ptr;
            int* rc;
        public:
            sp(PointerType* p);
            sp(const sp& rhs);
            sp(sp&& rhs);

            ~sp();

            PointerType& operator*();
            PointerType* operator*();
    };

    template<class PointerType>
    sp<PointerType>::sp(PointerType* p) {
        ptr = p;
        rc = new int(1);
    }

    template<class PointerType>
    sp<PointerType>::sp(const sp<PointerType>& rhs) {
        ptr = rhs.ptr;
        rc = rhs.rc;
        *rc = *rc + 1;
    }

    template<class PointerType>
    sp<PointerType>::sp(sp<PointerType>&& rhs) {
        ptr = rhs.ptr;
        rhs.ptr = nullptr;

        rc = rhs.rc;
    }

    template<class PointerType>
    sp<PointerType>::~sp() {
        *rc = *rc - 1;

        if(*rc == 0) {
            delete ptr;
        }
    }

    template<class PointerType>
    PointerType& sp<PointerType>::operator*() {
        return *(operator->());
    }

    template<class PointerType>
    PointerType* sp<PointerType>::operator*() {
        return ptr;
    }
}

#endif
