#include <iostream>

int main() {
    int begin = 00;
    int end = 10;

    START:
        if(begin < end) {
            std::cout << begin;
            begin = begin + 1;
            goto START;
        }

    return 0;
}
