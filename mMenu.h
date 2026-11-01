#ifndef MMENU_H
#define MMENU_H

#include <iostream>
#include "TopUp.h"

class MainMenu {
private:
    MLTopUpSystem topUpSystem;

    void displayPurchaseHistory() {
        std::cout << "\n PURCHASE HISTORY \n";
        std::cout << "No recent transactions found...\n";
        std::cout << "\n";
    }

    void displayAccountDetails() {
        std::cout << "\n ACCOUNT DETAILS \n";
        std::cout << "Account Name: \n";
        std::cout << "Loyalty Level: \n";
        std::cout << " \n";
    }

public:
    void displayMenu() {
        std::cout << "\n ------------- \n";
        std::cout << "              MAIN MENU              \n";
        std::cout << "\n";
        std::cout << "1. Top-up\n";
        std::cout << "2. Purchase History\n";
        std::cout << "3. Account Details\n";
        std::cout << "4. Exit\n";
        std::cout << "-----------------\n";
    }

    void run() {
        int choice = 0;

        while (true) {
            displayMenu();
            std::cout << "Enter your choice (1-4): ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "\nInvalid input. Enter a valid number.\n";
                continue;
            }

            switch (choice) {
                case 1:
                    topUpSystem.run();
                    break;
                case 2:
                    displayPurchaseHistory();
                    break;
                case 3:
                    displayAccountDetails();
                    break;
                case 4:
                    std::cout << "\nExiting application. Thank you!\n";
                    return;
                default:
                    std::cout << "\nInvalid choice. Only select an option between 1 - 4.\n";
                    break;
            }
        }
    }
};

#endif
