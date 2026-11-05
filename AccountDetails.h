#ifndef ACCOUNTDETAILS_H
#define ACCOUNTDETAILS_H

#include <iostream>
#include <string>
#include <iomanip>
#include "PurchaseHistory.h"
#include "payMethod.h"

class AccountDetails {
private:
    std::string username;
    PurchaseHistory& history;

public:
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
        
        // Show current BNPL Balance
        double currentBalance = PayMethod::globalInstallmentQueue.getTotalBalance();
        std::cout << "Outstanding Pay Later Balance: PHP " << std::fixed << std::setprecision(2) << currentBalance << '\n';
        
        std::cout << "------------------------------------------\n";

        // Has an option to pay early when has balance
        if (currentBalance > 0) {
            char choice;
            std::cout << "Would you like to pay early now? (Y/N): ";
            std::cin >> choice;
            
            if (choice == 'Y' || choice == 'y') {
                PayMethod::globalInstallmentQueue.processNextInstallment();
            }
        }

        std::cout << "\n--- RECENT ACCOUNT PURCHASES ---\n";
        history.displayAll(username); // Filters purchases by this username
        std::cout << "------------------------------------------\n";
    }
    
    void openHistoryMenu() const {
        history.run(username); // Opens the history menu for this user
    }
};

#endif