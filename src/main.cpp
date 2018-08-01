#include <iostream>

#include "../core/java_string/java_string.h"
#include "../core/smart_pointer/sp.h"

int main(int argc, char** argv) {
    mylib::jstr str1 = "abc";
    mylib::jstr str2 = "def";

    std::cout << mylib::jstr(str1.contains("a")) << "\n";

    return 0;
}
