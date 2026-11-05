#ifndef MMENU_H
#define MMENU_H

#include <iostream>
#include "PurchaseHistory.h"
#include "mLTopUp.h"
#include "wRTopUp.h"
#include "hokTopUp.h"
#include "AccountDetails.h"

class MainMenu {
private:
    PurchaseHistory history;      // declared first so it exists before others
    MLTopUpSystem mlTopUp;
    WRTopUpSystem wrTopUp;
    HOKTopUpSystem hokTopUp;
    AccountDetails account;

    void displayPurchaseHistory() {
        history.run();
    }

    void displayAccountDetails() {
        account.display();
    }
    
    void runTopUpMenu() {
        int choice = 0;
        while(true) {
            std::cout << "\n======== TOP-UP MENU ========\n";
            std::cout << "1. Mobile Legends (MLBB)\n";
            std::cout << "2. Wild Rift (WR)\n";
            std::cout << "3. Honor of Kings (HOK)\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "=============================\n";
            std::cout << "Select a game: ";
            
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "\nInvalid input.\n";
                continue;
            }
            
            if (choice == 1) mlTopUp.run();
            else if (choice == 2) wrTopUp.run();
            else if (choice == 3) hokTopUp.run();
            else if (choice == 0) break;
            else std::cout << "\nInvalid choice.\n";
        }
    }

public:
    MainMenu() 
        : mlTopUp(history), 
          wrTopUp(history), 
          hokTopUp(history),
          account(history) // Pass the shared history to AccountDetails
    {
        history.loadSampleData(); 
        
        // Optional: Pre-set a dummy account for demo purposes
        account.setDetails("Dustin", "123456789", "1234", "dustin@email.com");
    }

    void displayMenu() {
        std::cout << "\n ------------- \n";
        std::cout << "              MAIN MENU              \n";
        std::cout << "\n";
        std::cout << "1. Top-up Games\n";
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
                    runTopUpMenu();
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