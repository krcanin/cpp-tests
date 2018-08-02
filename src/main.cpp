#include <iostream>

#include "../core/java_string/java_string.h"
#include "../core/smart_pointer/sp.h"

// #java-style

class Starter {
    public:
        static void main(int argc, char** argv) {
            mylib::sp<mylib::jstr_t> str1 = new mylib::jstr_t("qwertz");
            mylib::sp<mylib::jstr_t> str2 = new mylib::jstr_t(argv[1]);

            std::cout << str1->starts_with(*str2);
        }
};

int main(int argc, char** argv) {
    Starter::main(argc, argv);
    return 0;
}
