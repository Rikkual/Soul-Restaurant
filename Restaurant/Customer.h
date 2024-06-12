//
// Created by Rikkual on 2024/5/29.
//

#ifndef Customer_H
#define Customer_H

#include "User.h"
#include "Config.h"

class Customer: public User {
private:
    int customerID = 0;
    string name;
    string phoneNumber;

public:
    Customer() = default;
    explicit Customer(const User& user);
    explicit Customer(const User& user, const string &_name, const string &_phoneNumber);
    void setCustomerID(const int &_customerID);
    void setName(const string &_name);
    void setPhoneNumber(const string &_phoneNumber);
    [[nodiscard]] int getCustomerID() const;
    [[nodiscard]] string getName() const;
    [[nodiscard]] string getPhoneNumber() const;
};


#endif //Customer_H
