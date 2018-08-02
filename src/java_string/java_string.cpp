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
    jstr_t::jstr_t() {
        s = new char[1];
        s[0] = '\0';

        n = 0;
    }

    jstr_t::jstr_t(const jstr_t& rhs) {
        s = new char[rhs.n + 1];
        n = rhs.n;

        for(int32_t i = 0; i < n; i += 1) {
            s[i] = rhs.s[i];
        }

        s[n] = '\0';
    }

    jstr_t::jstr_t(jstr_t&& rhs) {
        s = rhs.s;
        rhs.s = nullptr;

        n = rhs.n;
        rhs.n = 0;
    }

    jstr_t::jstr_t(char c) {
        n = 1;
        s = new char[2];
        s[n - 1] = c;
        s[n] = '\0';
    }

    jstr_t::jstr_t(const char* str) {
        n = strlen(str);
        s = new char[n + 1];

        for(int32_t i = 0; i < n; i += 1) {
            s[i] = str[i];
        }

        s[n] = '\0';
    }

    jstr_t::jstr_t(const char* str, int32_t length) {
        if(length < 0) throw std::runtime_error("Negative length disallowed");

        n = length;
        s = new char[n + 1];

        for(int32_t i = 0; i < n; i += 1) {
            s[i] = str[i];
        }

        s[n] = '\0';
    }

    jstr_t::jstr_t(const char* str, int32_t offset, int32_t count) {
        if(offset < 0) throw std::runtime_error("Negative offset-index disallowed");
        if(count < 0) throw std::runtime_error("Negative count-value disallowed");

        n = count;

        s = new char[n + 1];
        strncpy(s, str + offset, count);
        s[n] = '\0';
    }

    jstr_t::jstr_t(bool b) {
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

    jstr_t::jstr_t(int16_t value) {
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

    jstr_t::jstr_t(uint16_t value) {
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

    jstr_t::jstr_t(int32_t value) {
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

    jstr_t::jstr_t(uint32_t value) {
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

    jstr_t::jstr_t(int64_t value) {
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

    jstr_t::jstr_t(uint64_t value) {
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

    jstr_t::~jstr_t() {
        delete[] s;
    }

    char jstr_t::char_at(int32_t index) const {
        if(index < 0) throw std::runtime_error("Negative index disallowed");
        return s[index];
    }

    int32_t jstr_t::compare_to(jstr_t& other) const {
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

    int32_t jstr_t::compare_to_ignore_case(jstr_t& other) const {
        jstr_t _ = other.to_lower_case();
        return to_lower_case().compare_to(_);
    }

    jstr_t jstr_t::concat(jstr_t& other) const {
        int32_t result_n = n + other.n;
        char* result_str = new char[result_n + 1];

        for(int32_t i = 0; i < n; i += 1) {
            result_str[i] = s[i];
        }

        for(int32_t i = 0; i < other.n; i += 1) {
            result_str[n + i] = other.char_at(i);
        }

        result_str[result_n] = '\0';

        return jstr_t(result_str, result_n);
    }

    bool jstr_t::contains(jstr_t& other) const {
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

    bool jstr_t::ends_with(jstr_t& other) const {
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

    bool jstr_t::equals(jstr_t& other) const {
        return compare_to(other) == 0;
    }

    int32_t jstr_t::index_of(char c, int32_t from) const {
        if(from < 0) throw std::runtime_error("Negative from-index disallowed");

        for(int32_t i = from; i < n; i += 1) {
            if(s[i] == c) {
                return i;
            }
        }

        return -1;
    }

    int32_t jstr_t::index_of(char c) const {
        return index_of(c, 0);
    }

    int32_t jstr_t::index_of(jstr_t& other, int32_t from) const {
        if(from < 0) throw std::runtime_error("Negative from-index disallowed");

        if(n < other.n) {
            return -1;
        }

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
                return i;
            }
        }

        return -1;
    }

    int32_t jstr_t::index_of(jstr_t& other) const {
        return index_of(other, 0);
    }

    bool jstr_t::is_empty() {
        return n == 0;
    }

    int32_t jstr_t::last_index_of(char c, int32_t from) const {
        if(from < 0) throw std::runtime_error("Negative from-index disallowed");

        int32_t result = -1;

        for(int32_t i = from; i >= 0; i -= 1) {
            if(s[i] == c) {
                return i;
            }
        }

        return result;
    }

    int32_t jstr_t::last_index_of(char c) const {
        return last_index_of(c, n - 1);
    }

    int32_t jstr_t::last_index_of(jstr_t& other, int32_t from) const {
        if(from < 0) throw std::runtime_error("Negative from-index disallowed");

        if(n < other.n) {
            return -1;
        }

        int32_t min_n = std::min(n, other.n);

        for(int32_t i = from; i >= 0; i -= 1) {
            if((i - other.n) < 0) {
                return false;
            }

            bool success = true;
            int32_t j = 0;

            while(j < min_n) {
                if(s[i - j] != other.char_at(j)) {
                    success = false;
                    break;
                }

                j += 1;
            }

            if(success) {
                return i;
            }
        }

        return -1;
    }

    int32_t jstr_t::last_index_of(jstr_t& other) const {
        return last_index_of(other, n - 1);
    }

    int32_t jstr_t::length() const {
        return n;
    }

    bool jstr_t::matches(jstr_t& regex) const {
        throw std::runtime_error("Not implemented yet");
    }

    jstr_t jstr_t::repeat(int32_t amount) const {
        if(amount < 0) throw std::runtime_error("Negative amount disallowed");

        int32_t result_n = n * amount;
        char* result_str = new char[result_n + 1];

        for(int32_t j = 0; j < amount; j += 1) {
            for(int32_t i = 0; i < n; i += 1) {
                result_str[j * n + i] = s[i];
            }
        }

        return jstr_t(result_str, result_n);
    }

    jstr_t jstr_t::replace(char old_c, char new_c) const {
        char* result = new char[n + 1];
        char current;

        for(int32_t i = 0, j = n + 1; i < j; i += 1) {
            current = s[i];

            if(current == old_c) {
                result[i] = new_c;
            } else {
                result[i] = current;
            }
        }

        return jstr_t(result, n);
    }

    jstr_t jstr_t::replace_all(jstr_t& regex, jstr_t& replacement) const {
        throw std::runtime_error("Not implemented yet");
    }

    jstr_t jstr_t::replace_first(jstr_t& regex, jstr_t& replacement) const {
        throw std::runtime_error("Not implemented yet");
    }

    jstr_t* jstr_t::split(jstr_t& regex) const {
        throw std::runtime_error("Not implemented yet");
    }

    jstr_t* jstr_t::split(jstr_t& regex, int32_t limit) const {
        if(limit < 0) throw std::runtime_error("Negative limit disallowed");

        throw std::runtime_error("Not implemented yet");
    }

    bool jstr_t::starts_with(jstr_t& prefix) const {
        return starts_with(prefix, 0);
    }

    bool jstr_t::starts_with(jstr_t& prefix, int32_t offset) const {
        if(offset < 0) throw std::runtime_error("Negative offset disallowed");

        if((offset + prefix.n) > n) {
            return false;
        }

        for(int32_t i = 0; i < prefix.n; i += 1) {
            if(s[i + offset] != prefix.char_at(i)) {
                return false;
            }
        }

        return true;
    }

    jstr_t jstr_t::substring(int32_t start) const {
        return substring(start, n);
    }

    jstr_t jstr_t::substring(int32_t start, int32_t end) const {
        if(start < 0) throw std::runtime_error("Negative start-index disallowed");
        if(end < 0) throw std::runtime_error("Negative end-index disallowed");
        if(start > end) throw std::runtime_error("Start-index must be less than or equal to end-index");

        int32_t result_n = end - start;
        char* result_str = new char[result_n + 1];

        for(int32_t i = start; i < end; i += 1) {
            result_str[i - start] = s[i];
        }

        result_str[result_n] = '\0';

        return jstr_t(result_str, result_n);
    }

    char* jstr_t::to_char_array() const {
        char* result = new char[n];

        for(int32_t i = 0; i < n; i += 1) {
            result[i] = s[i];
        }

        return result;
    }

    jstr_t jstr_t::to_lower_case() const {
        char* result = new char[n + 1];

        for(int32_t i = 0, j = n + 1; i < j; i += 1) {
            if(s[i] >= 0x41 && s[i] <= 0x5A) {
                result[i] = s[i] + 0x20;
            } else {
                result[i] = s[i];
            }
        }

        return jstr_t(result, n);
    }

    jstr_t jstr_t::to_upper_case() const {
        char* result = new char[n + 1];

        for(int32_t i = 0, j = n + 1; i < j; i += 1) {
            if(s[i] >= 0x61 && s[i] <= 0x7A) {
                result[i] = s[i] - 0x20;
            } else {
                result[i] = s[i];
            }
        }

        return jstr_t(result, n);
    }

    jstr_t jstr_t::ltrim() const {
        int32_t i = 0;

        while(isspace(s[i])) {
            i += 1;
        }

        return jstr_t(s + i);
    }

    jstr_t jstr_t::rtrim() const {
        int32_t i = n - 1;

        while(i >= 0 && isspace(s[i])) {
            i -= 1;
        }

        return jstr_t(s, 0, i + 1);
    }

    jstr_t jstr_t::trim() const {
        return ltrim().rtrim();
    }

    jstr_t& jstr_t::operator=(const jstr_t& rhs) {
        this->~jstr_t();

        s = new char[rhs.n + 1];
        n = rhs.n;

        for(int32_t i = 0; i < n; i += 1) {
            s[i] = rhs.s[i];
        }

        s[n] = '\0';

        return *this;
    }

    jstr_t& jstr_t::operator=(jstr_t&& rhs) {
        this->~jstr_t();

        s = rhs.s;
        rhs.s = nullptr;

        n = rhs.n;
        rhs.n = 0;

        return *this;
    }

    jstr_t& jstr_t::operator=(const char* str) {
        this->~jstr_t();

        n = strlen(str);
        s = new char[n + 1];

        for(int32_t i = 0; i < n; i += 1) {
            s[i] = str[i];
        }

        s[n] = '\0';

        return *this;
    }
}
