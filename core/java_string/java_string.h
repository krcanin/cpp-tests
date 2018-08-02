#ifndef JAVA_STRING_H
#define JAVA_STRING_H

#include <iostream>
#include <cstdint>
#include <cstring>

namespace mylib {
    // https://docs.oracle.com/javase/9/docs/api/java/lang/String.html
    class jstr_t {
        private:
            char* s;
            int32_t n;
        public:
            jstr_t();
            jstr_t(const jstr_t& rhs);
            jstr_t(jstr_t&& rhs);
            jstr_t(char c);
            jstr_t(const char* str);
            jstr_t(const char* str, int32_t length);
            jstr_t(const char* str, int32_t offset, int32_t count);
            jstr_t(bool b);
            jstr_t(int16_t value);
            jstr_t(uint16_t value);
            jstr_t(int32_t value);
            jstr_t(uint32_t value);
            jstr_t(int64_t value);
            jstr_t(uint64_t value);

            ~jstr_t();

            char char_at(int32_t index) const;

            int32_t compare_to(jstr_t& other) const;
            int32_t compare_to_ignore_case(jstr_t& other) const;

            jstr_t concat(jstr_t& other) const;
            jstr_t concat(jstr_t&& other) const { return concat(static_cast<jstr_t&>(other)); }

            bool contains(jstr_t& other) const;
            bool contains(jstr_t&& other) const { return contains(static_cast<jstr_t&>(other)); }

            bool ends_with(jstr_t& other) const;

            bool equals(jstr_t& other) const;

            int32_t index_of(char c, int32_t from) const;
            int32_t index_of(char c) const;
            int32_t index_of(jstr_t& other, int32_t from) const;
            int32_t index_of(jstr_t& other) const;

            bool is_empty();

            int32_t last_index_of(char c, int32_t from) const;
            int32_t last_index_of(char c) const;
            int32_t last_index_of(jstr_t& other, int32_t from) const;
            int32_t last_index_of(jstr_t& other) const;

            int32_t length() const;

            bool matches(jstr_t& regex) const;

            jstr_t repeat(int32_t amount) const;

            jstr_t replace(char old_c, char new_c) const;
            jstr_t replace_all(jstr_t& regex, jstr_t& replacement) const;
            jstr_t replace_first(jstr_t& regex, jstr_t& replacement) const;

            jstr_t* split(jstr_t& regex) const; // HEAP - NOT MANAGED
            jstr_t* split(jstr_t& regex, int32_t limit) const; // HEAP - NOT MANAGED

            bool starts_with(jstr_t& prefix) const;
            bool starts_with(jstr_t& prefix, int32_t offset) const;

            jstr_t substring(int32_t start) const;
            jstr_t substring(int32_t start, int32_t end) const;

            char* to_char_array() const; // HEAP - NOT MANAGED

            jstr_t to_lower_case() const;
            jstr_t to_upper_case() const;

            jstr_t ltrim() const;
            jstr_t rtrim() const;
            jstr_t trim() const;

            jstr_t& operator=(const jstr_t&);
            jstr_t& operator=(jstr_t&& rhs);
            jstr_t& operator=(const char* str);
    };
}

namespace std {
    inline ostream& operator<<(ostream& os, const mylib::jstr_t& rhs) {
        for(int32_t i = 0; i < rhs.length(); i += 1) {
            os << rhs.char_at(i);
        }

        return os;
    }
}

#endif
