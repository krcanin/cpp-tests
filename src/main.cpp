#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>

#include "../libs/crap/binary_tree/avl_tree/avl_tree.h"

using namespace crap;

int main(int argc, char** argv) {
	avl_tree_t<int, int> at;
	at.insert(20, 0);
	at.insert(30, 0);
	at.insert(50, 0);
	at.insert(70, 0);
	at.insert(80, 0);
	at.insert(90, 0);
	at.insert(110, 0);

	auto it = at.begin();
	auto it2 = at.end();

	it = it + 6;

	std::cout << "\n";
	std::cout << at.length << "\n";
	std::cout << (*it).first;

	return 0;
}

#endif
