#include <iostream>

#include "../core/java_string/java_string.h"
#include "../core/smart_pointer/sp.h"

int main(int argc, char** argv) {
    mylib::jstr str1 = " asdf";
    mylib::jstr str2 = str1.ltrim();

    std::cout << str1 << "\n" << str2;

    return 0;
}
