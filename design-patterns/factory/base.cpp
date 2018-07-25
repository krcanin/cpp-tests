#include "base.h"

#include <iostream>

std::string base::get_name() {
    return this->name;
}

void base::set_name(std::string name) {
    this->name = name;
}
