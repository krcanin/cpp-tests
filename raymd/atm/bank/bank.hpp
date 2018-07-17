#ifndef BANK_HPP
#define BANK_HPP
#include "../customer/customer.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
class Bank {
	private:
		string name;
		vector<Customer> *customers;

	public:
		size_t length() {
			return customers->size();
		}

		Customer getCustomer(size_t index) {
			return (*(this->getCustomers()))[index];
		}

	public:
		string const &getName() const;
		void setName(string const &name);

	private:
		vector<Customer>* const getCustomers() const;
		void setCustomers(vector<Customer> *customers);

	public:
		Bank();
		Bank(string const &name);
		Bank(Bank &b);
		~Bank();

		bool equals(Bank &b);

		void addCustomer(Customer &c);

		operator string() {
			string text = "[Name]: " + this->getName() + "\n";
			for(auto it = this->getCustomers()->begin(); it != this->getCustomers()->end(); ++it){
				text += (*it);
				text += "\n";
			}
			return text;
		}
};

inline ostream &operator<<(ostream &os, Bank &b){
	return (os << static_cast<string>(b));
}

#endif
