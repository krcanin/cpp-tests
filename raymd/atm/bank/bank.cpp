#include "bank.hpp"
#include "../customer/customer.hpp"
#include <string>
#include <vector>

string const &Bank::getName() const{
	return this->name;
}

void Bank::setName(string const &name){
	this->name = name;
}

vector<Customer>* const Bank::getCustomers() const{
	return this->customers;
}

void Bank::setCustomers(vector<Customer> *customers){
	this->customers = customers;
}

Bank::Bank(): Bank("Default Bank"){}

Bank::Bank(string const &name){
	this->setName(name);
	this->setCustomers(new vector<Customer>(0));
}

Bank::Bank(Bank &b): name(b.name){
	this->setCustomers(new vector<Customer>());

	// for(auto it : *(this->customers)){
	// 	nc->push_back(it);
	// }

	for(auto it = b.getCustomers()->begin(); it != b.getCustomers()->end(); ++it){
		this->getCustomers()->push_back(*it);
	}
}

Bank::~Bank(){
	delete this->getCustomers();
}

// string const Bank::toString(){
// 	string text = "[Name]: " + this->getName() + "\n";
// 	for(auto it = this->getCustomers()->begin(); it != this->getCustomers()->end(); ++it){
// 		text += (*it);
// 		text += "\n";
// 	}
// 	return text;
// }

bool Bank::equals(Bank &b){
	return (this->getName() == b.getName());
}

void Bank::addCustomer(Customer &c){

	string randomString {""};
	for(int i = 0; i < 10; i++){
		randomString += to_string(rand() % 10);
	}

	c.setNr(stol(randomString));

	this->getCustomers()->push_back(c);
}
