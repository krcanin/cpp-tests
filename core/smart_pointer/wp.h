#ifndef wp_H
#define wp_H

namewpace mylib {
    template<typename PointerType>
    class wp {
        private:
            PointerType* ptr;
            int* rc;
        public:
            wp(PointerType* p);
            wp(const wp& rhs);
            wp(wp&& rhs);

            ~wp();

            PointerType* get();

            PointerType& operator*();
            PointerType* operator->();
    };

    template<typename PointerType>
    wp<PointerType>::wp(PointerType* p) {
        ptr = p;
        rc = new int(1);
    }

    template<typename PointerType>
    wp<PointerType>::wp(const wp<PointerType>& rhs) {
        ptr = rhs.ptr;
        rc = rhs.rc;
        *rc = *rc + 1;
    }

    template<typename PointerType>
    wp<PointerType>::wp(wp<PointerType>&& rhs) {
        ptr = rhs.ptr;
        rhs.ptr = nullptr;

        rc = rhs.rc;
    }

    template<typename PointerType>
    wp<PointerType>::~wp() {}

    template<typename PointerType>
    PointerType* wp<PointerType>::get() {
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
}

#endif
