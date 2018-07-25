#include <iostream>

class a {};

class factory {
    public:
        a* create() {
            return new a();
        }
};

int main() {
    factory f;
    a a = f.create();

    return 0;
}
