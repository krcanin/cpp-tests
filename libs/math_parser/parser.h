#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

namespace crap {
    namespace math_parser {
        class parser_t {
            private:
                lexer_t& l;
            public:
                parser_t(lexer_t& l);
        }

        parser_t::parser_t(lexer_t& l) : l(l) {}
    }
}

#endif
