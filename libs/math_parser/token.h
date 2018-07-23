#ifndef TOKEN_H
#define TOKEN_H

#include <limits>
#include <string>

namespace mylib {
    namespace math_parser {
        enum token_type_t { NUM, PLUS, MINUS, LPAREN, RPAREN };

        struct token_t {
            std::string text;
            token_type_t type;
        };
    }
}

#endif
