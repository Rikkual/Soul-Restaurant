//
// Created by Rikkual on 2024/5/29.
//

#include "Customer.h"

Customer::Customer(const User &user) {
    username = user.getUserName();
    password = user.getPassword();
}

Customer::Customer(const User &user, const string &_name, const string &_phoneNumber): Customer(user) {
    name = _name;
    phoneNumber = _phoneNumber;
}

void Customer::setCustomerID(const int &_customerID) {
    customerID = _customerID;
}

void Customer::setName(const string &_name) {
    name = _name;
}

void Customer::setPhoneNumber(const string &_phoneNumber) {
    phoneNumber = _phoneNumber;
}

int Customer::getCustomerID() const {
    return customerID;
}

string Customer::getName() const {
    return name;
}

string Customer::getPhoneNumber() const {
    return phoneNumber;
}

