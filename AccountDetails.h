#ifndef ACCOUNTDETAILS_H
#define ACCOUNTDETAILS_H

#include <iostream>
#include <string>

class AccountDetails {
private:
    std::string username;
    std::string playerID;
    std::string zoneID;
    std::string email;

public:
    AccountDetails(
        const std::string& name = "Guest",
        const std::string& pID = "Not Set",
        const std::string& zID = "Not Set",
        const std::string& mail = "Not Set"
    ) : username(name), playerID(pID), zoneID(zID), email(mail) {}

    void setDetails(const std::string& name, const std::string& pID, const std::string& zID, const std::string& mail) {
        username = name;
        playerID = pID;
        zoneID = zID;
        email = mail;
    }

    void display() const {
        std::cout << "\n========== ACCOUNT DETAILS ==========\n";
        std::cout << "Username          : " << username << '\n';
        std::cout << "Player ID         : " << playerID << '\n';
        std::cout << "Zone ID           : " << zoneID << '\n';
        std::cout << "Email             : " << email << '\n';
        std::cout << "=====================================\n";
    }
};

#endif