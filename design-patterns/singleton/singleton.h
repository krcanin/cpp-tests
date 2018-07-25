#include <iostream>

class singleton_t {
    private:
        singleton_t();
        singleton_t(const singleton_t& rhs) = delete;
        singleton_t& operator=(const singleton_t& rhs) = delete;
    public:
        ~singleton_t();
        static singleton_t& instance();
        void print(std::ostream& os = std::cout);
};
