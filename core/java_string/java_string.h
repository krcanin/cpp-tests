#ifndef JAVA_STRING_H
#define JAVA_STRING_H

#include <iostream>
#include <cstdint>
#include <cstring>

namespace mylib {
    class jstr {
        private:
            char* s;
            uint32_t n;
        public:
            const uint32_t& length = n;

            jstr();
            jstr(const jstr& rhs);
            jstr(jstr&& rhs);
            jstr(const char* str);

            ~jstr();

            jstr& operator=(const jstr&);
            jstr& operator=(jstr&& rhs);
            jstr& operator=(const char* str);

            char& operator[](uint32_t i) const;

            jstr operator+(const jstr& rhs) const;
            jstr& operator+=(const jstr& rhs);

            jstr operator*(uint32_t amount) const;
            jstr& operator*=(uint32_t amount);
    };
}

namespace std {
    inline ostream& operator<<(ostream& os, const mylib::jstr& rhs) {
        for(uint32_t i = 0; i < rhs.length; i += 1) {
            os << rhs[i];
        }

        return os;
    }
}

#endif
