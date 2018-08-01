#include "../../core/java_string/java_string.h"

template<typename T>
int32_t digit_length(T value) {
    if(value == 0) {
        return 1;
    }

    int32_t result = value < 0 ? 1 : 0; // preserve space for '-'-sign

    while(value != 0) {
        result += 1;
        value /= 10;
    }

    return result;
}

namespace mylib {
    jstr::jstr() {
        s = new char[1];
        s[0] = '\0';

        n = 0;
    }

    jstr::jstr(const jstr& rhs) {
        s = new char[rhs.n + 1];
        n = rhs.n;

        for(int32_t i = 0; i < n; i += 1) {
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

    jstr::jstr(char c) {
        n = 1;
        s = new char[2];
        s[n - 1] = c;
        s[n] = '\0';
    }

    jstr::jstr(const char* str) {
        n = strlen(str);
        s = new char[n + 1];

        for(int32_t i = 0; i < n; i += 1) {
            s[i] = str[i];
        }

        s[n] = '\0';
    }

    jstr::jstr(const char* str, int32_t length) {
        n = length;
        s = new char[n + 1];

        for(int32_t i = 0; i < n; i += 1) {
            s[i] = str[i];
        }

        s[n] = '\0';
    }

    jstr::jstr(const char* str, int32_t offset, int32_t count) {
        if(offset < 0) throw "Negative offset-index disallowed";
        if(count < 0) throw "Negative count-value disallowed";

        n = count;

        s = new char[n + 1];
        strncpy(s, str + offset, count);
        s[n] = '\0';
    }

    jstr::jstr(bool b) {
        if(b) {
            n = 4;

            s = new char[n + 1];
            strcpy(s, "true");
            s[n] = '\0';
        } else {
            n = 5;

            s = new char[n + 1];
            strcpy(s, "false");
            s[n] = '\0';
        }
    }

    jstr::jstr(int16_t value) {
        n = digit_length(value);
        s = new char[n + 1];

        if(value == 0) {
            s[0] == '0';
        } else {
            if(value < 0) {
                s[0] = '-';
            }

            int32_t i = n - 1;

            while(value != 0) {
                s[i--] = abs(value % 10) + 0x30;
                value = value / 10;
            }
        }

        s[n] = '\0';
    }

    jstr::jstr(uint16_t value) {
        n = digit_length(value);
        s = new char[n + 1];

        if(value == 0) {
            s[0] == '0';
        } else {
            int32_t i = n - 1;

            while(value != 0) {
                s[i] = (value % 10) + 0x30;
                i -= 1;
                value = value / 10;
            }
        }

        s[n] = '\0';
    }

    jstr::jstr(int32_t value) {
        n = digit_length(value);
        s = new char[n + 1];

        if(value == 0) {
            s[0] == '0';
        } else {
            if(value < 0) {
                s[0] = '-';
            }

            int32_t i = n - 1;

            while(value != 0) {
                s[i] = abs(value % 10) + 0x30;
                i -= 1;
                value = value / 10;
            }
        }

        s[n] = '\0';
    }

    jstr::jstr(uint32_t value) {
        n = digit_length(value);
        s = new char[n + 1];

        if(value == 0) {
            s[0] == '0';
        } else {
            int32_t i = n - 1;

            while(value != 0) {
                s[i] = (value % 10) + 0x30;
                i -= 1;
                value = value / 10;
            }
        }

        s[n] = '\0';
    }

    jstr::jstr(int64_t value) {
        n = digit_length(value);
        s = new char[n + 1];

        if(value == 0) {
            s[0] == '0';
        } else {
            if(value < 0) {
                s[0] = '-';
            }

            int32_t i = n - 1;

            while(value != 0) {
                s[i] = abs(value % 10) + 0x30;
                i -= 1;
                value = value / 10;
            }
        }

        s[n] = '\0';
    }

    jstr::jstr(uint64_t value) {
        n = digit_length(value);
        s = new char[n + 1];

        if(value == 0) {
            s[0] == '0';
        } else {
            int32_t i = n - 1;

            while(value != 0) {
                s[i] = (value % 10) + 0x30;
                i -= 1;
                value = value / 10;
            }
        }

        s[n] = '\0';
    }

    jstr::~jstr() {
        delete[] s;
    }

    char jstr::char_at(int32_t index) const {
        if(index < 0) throw "Negative index disallowed";
        return s[index];
    }

    int32_t jstr::compare_to(jstr& other) const {
        for(int32_t i = 0, j = std::min(n, other.n); i < j; i += 1) {
            if(s[i] != other.char_at(i)) {
                return s[i] - other.char_at(i);
            }
        }

        if(n < other.n) {
            return -1;
        } else if(n > other.n) {
            return 1;
        } else {
            return 0;
        }
    }

    int32_t jstr::compare_to_ignore_case(jstr& other) const {
        jstr other_ = other.to_lower_case();
        return to_lower_case().compare_to(other_);
    }

    jstr jstr::concat(jstr& other) const {
        int32_t result_n = n + other.n;
        char* result_str = new char[result_n + 1];

        for(int32_t i = 0; i < n; i += 1) {
            result_str[i] = s[i];
        }

        for(int32_t i = 0; i < other.n; i += 1) {
            result_str[n + i] = other.char_at(i);
        }

        result_str[result_n] = '\0';

        return jstr(result_str, result_n);
    }

    bool jstr::contains(jstr& other) const {
        if(n < other.n) {
            return false;
        }

        int32_t min_n = std::min(n, other.n);

        for(int32_t i = 0; i < n; i += 1) {
            if((i + other.n) > n) {
                return false;
            }

            bool success = true;
            int32_t j = 0;

            while(j < min_n) {
                if(s[i + j] != other.char_at(j)) {
                    success = false;
                    break;
                }

                j += 1;
            }

            if(success) {
                return true;
            }
        }

        return false;
    }

    bool jstr::ends_with(jstr& other) const {
        if(n < other.n) {
            return false;
        }

        int32_t i_this = n - 1;
        int32_t i_other = other.n - 1;
        int32_t end = n - other.n;

        while(i_this >= end) {
            if(s[i_this] != other.char_at(i_other)) {
                return false;
            }

            i_this -= 1;
            i_other -= 1;
        }

        return true;
    }

    bool jstr::equals(jstr& other) const {
        return compare_to(other) == 0;
    }

    int32_t jstr::index_of(char c, int32_t from) const {
        if(from < 0) throw "Negative from-index disallowed";

        for(int32_t i = from; i < n; i += 1) {
            if(s[i] == c) {
                return i;
            }
        }

        return -1;
    }

    int32_t jstr::index_of(char c) const {
        return index_of(c, 0);
    }

    int32_t jstr::index_of(jstr& other, int32_t from) const {
        if(from < 0) throw "Negative from-index disallowed";

        if(n < other.n) {
            return -1;
        }

        int32_t result = -1;
        int32_t min_n = std::min(n, other.n);

        for(int32_t i = from; i < n; i += 1) {
            if((i + other.n) > n) {
                return false;
            }

            bool success = true;
            int32_t j = 0;

            while(j < min_n) {
                if(s[i + j] != other.char_at(j)) {
                    success = false;
                    break;
                }

                j += 1;
            }

            if(success) {
                result = i;
            }
        }

        return result;
    }

    int32_t jstr::index_of(jstr& other) const {
        return index_of(other, 0);
    }

    bool jstr::is_empty() {
        return n == 0;
    }

    int32_t jstr::last_index_of(char c, int32_t from) const {
        if(from < 0) throw "Negative from-index disallowed";

        int32_t result = -1;

        for(int32_t i = from; i < n; i += 1) {
            if(s[i] == c) {
                result = i;
            }
        }

        return result;
    }

    int32_t jstr::last_index_of(char c) const {
        return last_index_of(c, n - 1);
    }

    int32_t jstr::last_index_of(jstr& other, int32_t from) const {
        if(from < 0) throw "Negative from-index disallowed";

        if(n < other.n) {
            return -1;
        }

        int32_t result = -1;
        int32_t min_n = std::min(n, other.n);

        for(int32_t i = from; i < n; i += 1) {
            if((i + other.n) > n) {
                return false;
            }

            bool success = true;
            int32_t j = 0;

            while(j < min_n) {
                if(s[i + j] != other.char_at(j)) {
                    success = false;
                    break;
                }

                j += 1;
            }

            if(success) {
                result = i;
            }
        }

        return result;
    }

    int32_t jstr::last_index_of(jstr& other) const {
        return last_index_of(other, n - 1);
    }

    int32_t jstr::length() const {
        return n;
    }

    bool jstr::matches(jstr& regex) const {

    }

    jstr jstr::repeat(int32_t amount) const {
        if(amount < 0) throw "Negative amount disallowed";

        int32_t result_n = n * amount;
        char* result_str = new char[result_n + 1];

        for(int32_t j = 0; j < amount; j += 1) {
            for(int32_t i = 0; i < n; i += 1) {
                result_str[j * n + i] = s[i];
            }
        }

        return jstr(result_str, result_n);
    }

    jstr jstr::replace(char old_c, char new_c) const {

    }

    jstr jstr::replace_all(jstr& regex, jstr& replacement) const {

    }

    jstr jstr::replace_first(jstr& regex, jstr& replacement) const {

    }

    jstr* jstr::split(jstr& regex) const {
        return split(regex, INT32_MAX);
    }

    jstr* jstr::split(jstr& regex, int32_t limit) const {
        if(limit < 0) throw "Negative limit disallowed";

    }

    bool jstr::starts_with(jstr& prefix) const {
        return starts_with(prefix, 0);
    }

    bool jstr::starts_with(jstr& prefix, int32_t offset) const {
        if(offset < 0) throw "Negative offset disallowed";

    }

    jstr jstr::substring(int32_t start) const {
        return substring(start, n);
    }

    jstr jstr::substring(int32_t start, int32_t end) const {
        if(start < 0) throw "Negative start-index disallowed";
        if(end < 0) throw "Negative end-index disallowed";

    }

    char* jstr::to_char_array() const {
        char* result = new char[n];

        for(int32_t i = 0; i < n; i += 1) {
            result[i] = s[i];
        }

        return result;
    }

    jstr jstr::to_lower_case() const {

    }

    jstr jstr::to_upper_case() const {

    }

    jstr jstr::ltrim() const {
        int32_t i = 0;

        while(isspace(s[i])) {
            i += 1;
        }

        return jstr(s + i);
    }

    jstr jstr::rtrim() const {
        int32_t i = n - 1;

        while(i >= 0 && isspace(s[i])) {
            i -= 1;
        }

        return jstr(s, 0, i + 1);
    }

    jstr jstr::trim() const {
        return ltrim().rtrim();
    }

    jstr& jstr::operator=(const jstr& rhs) {
        this->~jstr();

        s = new char[rhs.n + 1];
        n = rhs.n;

        for(int32_t i = 0; i < n; i += 1) {
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

        for(int32_t i = 0; i < n; i += 1) {
            s[i] = str[i];
        }

        s[n] = '\0';

        return *this;
    }
}

#undef char
