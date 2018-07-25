#ifndef BASE_H
#define BASE_H

#include <string>

class base {
    private:
        std::string name;
    public:
        std::string get_name();
        void set_name(std::string name);
};

#endif
