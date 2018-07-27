#include <iostream>

#include "../core/java_string/java_string.h"

int main(int argc, char** argv) {
    mylib::jstr js;

    js = "a";
    std::cout << js << std::endl;

    js += "c";
    std::cout << js << std::endl;

    js = js + "b";
    std::cout << js << std::endl;

    js *= 4;
    std::cout << js << std::endl;

    std::cout << js.length << std::endl;

    return 0;
}
