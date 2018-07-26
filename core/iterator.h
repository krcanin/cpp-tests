#ifndef ITERATOR_H
#define ITERATOR_H

template<typename T>
class forward_iterator_i {
	public:
		virtual bool eof() = 0;

		virtual void next() = 0;

		virtual T peek() = 0;

		virtual T pop() {
			T result = peek();
			next();
			return result;
		}
};

template<typename T>
class iterator_i : public forward_iterator_i<T> {
    public:
        virtual void prev() = 0;
        
        virtual T pop(bool) {
            T result = this->peek();
            prev();
            return result;
        }
};

#endif

