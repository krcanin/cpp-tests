#ifndef LEXER_H
#define LEXER_H

#include <string>

#include "reader.h"
#include "token.h"

namespace mylib {
    namespace math_parser {
        class lexer_t {
            private:
                reader_t& r;
            public:
                lexer_t(reader_t& r);

                bool eof() const;
                token_t pop();
        };

        lexer_t::lexer_t(reader_t& r) : r(r) {}

        bool lexer_t::eof() const {
            return r.eof();
        }

        token_t lexer_t::pop() {
            char c;
            c = r.pop();

            token_t t;

            if(c >= 0x31 && c <= 0x39) {
                // c is digit, t is NUM
                t.text += c;
                t.type = token_type_t::NUM;

                while(true) {
                    c = r.peek();

                    if(c >= '0' && c <= '9') {
                        r.pop();
                        t.text += c;
                    } else if(c == '+' || c == '-' || c == '(' || c == ')') {
                        break;
                    } else {
                        std::string s = "Unknown token [";
                        s += r.index;
                        s += "]: ";
                        s += c;
                        throw s;
                    }
                }
            } else if(c == '+') {
                t.text += c;
                t.type = token_type_t::PLUS;
            } else if(c == '-') {
                t.text += c;
                t.type = token_type_t::MINUS;
            } else if(c == '(') {
                t.text += c;
                t.type = token_type_t::LPAREN;
            } else if(c == ')') {
                t.text += c;
                t.type = token_type_t::RPAREN;
            } else {
                std::string s = "Unknown token [";
                s += std::to_string(r.index);
                s += "]: ";
                s += c;
                throw s;
            }

            return t;
        }
    }
}

#endif
