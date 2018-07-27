#include "../core/java_string/java_string.h"

namespace mylib {
    jstr::jstr() {
        s = new char[1];
        s[0] = '\0';

        n = 0;
    }

    jstr::jstr(const jstr& rhs) {
        s = new char[rhs.n + 1];
        n = rhs.n;

        for(uint32_t i = 0; i < n; i += 1) {
            s[i] = rhs.s[i];
        }

        s[n] = '\0';
    }

    jstr::jstr(jstr&& rhs) {
        s = rhs.s;
        rhs.s = nullptr;

        n = rhs.n;
        rhs.n = 0;
    }

    jstr::jstr(const char* str) {
        n = strlen(str);
        s = new char[n + 1];

        for(uint32_t i = 0; i < n + 1; i += 1) {
            s[i] = str[i];
        }

        s[n] = '\0';
    }

    jstr::~jstr() {
        delete[] s;
    }

    jstr& jstr::operator=(const jstr& rhs) {
        this->~jstr();

        s = new char[rhs.n + 1];
        n = rhs.n;

        for(uint32_t i = 0; i < n; i += 1) {
            s[i] = rhs.s[i];
        }

        s[n] = '\0';

        return *this;
    }

    jstr& jstr::operator=(jstr&& rhs) {
        this->~jstr();

        s = rhs.s;
        rhs.s = nullptr;

        n = rhs.n;
        rhs.n = 0;

        return *this;
    }

    jstr& jstr::operator=(const char* str) {
        this->~jstr();

        n = strlen(str);
        s = new char[n + 1];

        for(uint32_t i = 0; i < n; i += 1) {
            s[i] = str[i];
        }

        s[n] = '\0';

        return *this;
    }

    char& jstr::operator[](uint32_t i) const {
        return s[i];
    }

    jstr jstr::operator+(const jstr& rhs) const {
        jstr result;
        result.~jstr();

        result.n = n + rhs.n;
        result.s = new char[result.n + 1];

        for(uint32_t i = 0; i < n; i += 1) {
            result.s[i] = operator[](i); // (*this)[i]
        }

        for(uint32_t i = 0; i < rhs.n; i += 1) {
            result.s[n + i] = rhs[i];
        }

        return result;
    }

    jstr& jstr::operator+=(const jstr& rhs) {
        return operator=(operator+(rhs));
    }

    jstr jstr::operator*(uint32_t amount) const {
        jstr result;
        result.~jstr();

        result.n = n * amount;
        result.s = new char[result.n + 1];

        for(uint32_t j = 0; j < amount; j += 1) {
            for(uint32_t i = 0; i < n; i += 1) {
                result.s[j * n + i] = operator[](i); // (*this)[i]
            }
        }

        return result;
    }

    jstr& jstr::operator*=(uint32_t amount) {
        return operator=(operator*(amount));
    }
}
