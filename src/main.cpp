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

	for(auto p : at) {
		auto& key = p.first;
		auto& value = p.second;

		std::cout << key << " ";
		key = key + 1;
	}

	std::cout << "\n";

	for(auto p : at) {
		auto& key = p.first;
		std::cout << key << " ";
	}

	return 0;
}

#endif
