#include "factory.h"

#include "derived/foo.h"
#include "derived/bar.h"

base factory_t::create(char c) {
    if(c == 'f') {
        foo result;
        return result;
    } else if(c == 'b') {
        bar result;
        return result;
    } else {
        throw "Invalid input";
    }
}
