#include <iostream>

#include "factory.h"

void say_hello(base& rhs) {
    std::cout << rhs.get_name() << std::endl;
}

int main() {
    base f = factory_t::create(factory_product_e::FOO);
    base b = factory_t::create(factory_product_e::BAR);

    say_hello(f);
    say_hello(b);

    return 0;
}
