#ifndef ACCOUNTDETAILS_H
#define ACCOUNTDETAILS_H

#include <iostream>
#include <string>

class AccountDetails {
private:
    std::string username;
    std::string gameUID;
    std::string gmail;

public:
    AccountDetails(
        const std::string& name,
        const std::string& uid,
        const std::string& email
    ) : username(name), gameUID(uid), gmail(email) {
    }

    void display() const {
        std::cout << "\n========== ACCOUNT DETAILS ==========\n";
        std::cout << "Username          : " << username << '\n';
        std::cout << "Game UID: " << gameUID << '\n';
        std::cout << "Gmail             : " << gmail << '\n';
        std::cout << "=====================================\n";
    }
};

#endif