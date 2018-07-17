#include <iostream>
#include <string>

#include "customer/customer.hpp"
#include "bank/bank.hpp"
#include "menu/menu.hpp"

using namespace std;

int main() {
	string s;

	cout << "Name der Bank: ";
	getline(cin, s);

	Bank b(s);
	showMenu(b);

	return 0;
}
