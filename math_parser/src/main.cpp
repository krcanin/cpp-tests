#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <string>

#include "../libs/math_parser/reader.h"
#include "../libs/math_parser/lexer.h"

using namespace mylib::math_parser;

int main(int argc, char** argv) {
    char* s = const_cast<char*>("42-(30+69)");
    reader_t r(s);
    lexer_t l(r);

    while(!l.eof()) {
        try {
            auto t = l.pop();
            std::cout << "'" << t.text << "'\n" << std::flush;
        } catch(std::string err) {
            std::cout << err;
        }
    }

    return 0;
}

#endif
