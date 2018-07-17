#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <string>
#include <iostream>

using namespace std;

class Customer {
	private:
		string name;
		long nr;
		int pin;

	public:
		string const &getName() const;
		void setName(string const &name);

		long const &getNr() const;
		void setNr(long const &nr);

		int const &getPin() const;
		void setPin(int const &pin);

		Customer();
		Customer(string const &name);
		Customer(string const &name, int pin);
		~Customer();

		bool equals(Customer &c);
		// string const toString();

		operator string(){
			return "[Name]: " + this->getName() + " [Nr]: " + to_string(this->getNr()) + " [Pin]: " + to_string(this->getPin());
		}
};

inline ostream &operator<<(ostream &os, Customer &c){
	os << c;
	return os;
}

#endif
