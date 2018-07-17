#include <iostream>

class A {
    private:
        int _x;
    public:
        A(int x = 0) {
            _x = x;
        }
        
        A& operator+=(int x) {
            _x += x;
            return *this;
        }
        
        operator int() {
            return _x;
        }
};

class B {
    private:
        
    public:
        A age;
        
        B(int x) : age(x) {
            
        }
};

int main2(int argc, char** argv) {
    B xyz(42);
    std::cout << xyz.age << "\n";
    (xyz.age += 5) += 5;
    std::cout << xyz.age << "\n";
    
    
    return 0;
}

