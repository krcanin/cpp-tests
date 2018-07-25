#include "singleton.h"

singleton_t::singleton_t() {}

singleton_t::~singleton_t() {}

singleton_t& singleton_t::instance() {
    static singleton_t first;
    return first;
}

void singleton_t::print(std::ostream& os) {
    os << "Hello, world!";
}
