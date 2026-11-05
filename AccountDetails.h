#ifndef ACCOUNTDETAILS_H
#define ACCOUNTDETAILS_H

#include <iostream>
#include <string>
#include "PurchaseHistory.h"

class AccountDetails {
private:
    std::string username;
    PurchaseHistory& history; // Reference to shared history

public:
    // Initializer list is in the same order the members are declared above
    AccountDetails(
        PurchaseHistory& h,
        const std::string& name = "Guest"
    ) : username(name), history(h) {}

    void setDetails(const std::string& name) {
        username = name;
    }

    void display() const {
        std::cout << "\n----------- ACCOUNT DETAILS ----------\n";
        std::cout << "Username          : " << username << '\n';
        std::cout << "------------------------------------------\n";

        std::cout << "\n--- RECENT ACCOUNT PURCHASES ---\n";
        history.displayAll();
        std::cout << "------------------------------------------\n";
    }
};

#endif