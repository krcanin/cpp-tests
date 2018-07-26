#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include "../core/smart_pointer/sp.h"
#include <chrono>
#include <thread>

using namespace mylib;

int main(int argc, char** argv) {
    while(true) {
        sp<int> p1 = new int(42);
        sp<int> p2 = p1;
        sp<int> p3 = p1;
        sp<int> p4 = std::move(p2);

        std::cout << *p1 << "\n";
        std::cout << *p2 << "\n";
        std::cout << *p4 << "\n\n";
    }

    return 0;
}

#endif
