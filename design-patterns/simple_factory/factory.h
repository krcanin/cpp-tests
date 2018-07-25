#ifndef FACTORY_H
#define FACTORY_H

#include "base.h"

enum factory_product_e { FOO, BAR };

class factory_t {
    public:
        static base create(factory_product_e c);
};

#endif
