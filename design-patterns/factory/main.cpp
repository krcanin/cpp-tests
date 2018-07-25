#include <iostream>

#include "factory.h"

void say_hello(base& rhs) {
    std::cout << rhs.get_name() << std::endl;
}

int main() {
    base f = factory_t::create('f');
    base b = factory_t::create('b');

    say_hello(f);
    say_hello(b);

    return 0;
}
