#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>

#include "../libs/binary_tree/binary_heap/binary_heap.h"

using namespace crap;

int main(int argc, char** argv) {
	binary_heap_t<int, int> bh;
	bh.insert(20, 0);
	bh.insert(30, 0);
	bh.insert(50, 0);
	bh.insert(70, 0);
	bh.insert(80, 0);
	bh.insert(90, 0);

	for(auto x : bh._data) {
		std::cout << x->key << " ";
	}

	return 0;
}

#endif
