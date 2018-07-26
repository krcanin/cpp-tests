#ifndef SP_H
#define SP_H

namespace mylib {
    template<typename PointerType>
    class sp {
        private:
            PointerType* ptr;
            int* rc;
        public:
            sp();
            sp(PointerType* p);
            sp(const sp<PointerType>& rhs);
            sp(sp<PointerType>&& rhs);

            ~sp();

            operator PointerType*();

            PointerType& operator*();
            PointerType* operator->();

            sp<PointerType>& operator=(PointerType* rhs);
            sp<PointerType>& operator=(const sp<PointerType>& rhs);
            sp<PointerType>& operator=(sp<PointerType>&& rhs);
    };

    template<typename PointerType>
    sp<PointerType>::sp() {
        ptr = nullptr;
        rc = nullptr;
    }

    template<typename PointerType>
    sp<PointerType>::sp(PointerType* p) {
        ptr = p;

        if(p) {
            rc = new int(1);
        } else {
            rc = nullptr;
        }
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
        rhs.rc = nullptr;
    }

    template<typename PointerType>
    sp<PointerType>::~sp() {
        if(rc) {
            *rc = *rc - 1;

            if(*rc == 0) {
                delete rc;
                delete ptr;
            }
        }
    }

    template<typename PointerType>
    sp<PointerType>::operator PointerType*() {
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

    template<typename PointerType>
    sp<PointerType>& sp<PointerType>::operator=(PointerType* rhs) {
        this->~sp();

        ptr = rhs;

        if(rhs) {
            rc = new int(1);
        } else {
            rc = nullptr;
        }
    }

    template<typename PointerType>
    sp<PointerType>& sp<PointerType>::operator=(const sp<PointerType>& rhs) {
        this->~sp();

        ptr = rhs.ptr;
        rc = rhs.rc;
        *rc = *rc + 1;
    }

    template<typename PointerType>
    sp<PointerType>& sp<PointerType>::operator=(sp<PointerType>&& rhs) {
        this->~sp();

        ptr = rhs.ptr;
        rhs.ptr = nullptr;

        rc = rhs.rc;
        rhs.rc = nullptr;
    }
}

#endif
