#include "factory.h"

#include "foo.h"
#include "bar.h"

base factory_t::create(factory_product_e c) {
    if(c == factory_product_e::FOO) {
        foo result;
        return result;
    } else if(c == factory_product_e::BAR) {
        bar result;
        return result;
    } else {
        throw "Invalid input";
    }
}
