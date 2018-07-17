#include "customer.hpp"
#include <string>
using namespace std;

string const &Customer::getName() const{
	return this->name;
}

void Customer::setName(string const &name){
	this->name = name;
}

long const &Customer::getNr() const{
	return this->nr;
}

void Customer::setNr(long const &nr){
	this->nr = nr;
}

int const &Customer::getPin() const{
	return this->pin;
}

void Customer::setPin(int const &pin){
	this->pin = pin;
}

Customer::Customer(): Customer("Default Customer"){}

Customer::Customer(string const &name): Customer(name, 0){}

Customer::Customer(string const &name, int pin){
	this->setName(name);
	this->setPin(pin);
}

Customer::~Customer(){
}

// string const Customer::toString(){
// 	return "[Name]: " + this->getName() + " [Nr]: " + to_string(this->getNr()) + " [Pin]: " + to_string(this->getPin());
// }

bool Customer::equals(Customer &c){
	return (this->getName() == c.getName());
}
