#ifndef MMENU_H
#define MMENU_H

#include <iostream>
#include <string>
#include <cctype>

#include "Login.h"
#include "PurchaseHistory.h"
#include "mLTopUp.h"
#include "wRTopUp.h"
#include "hokTopUp.h"
#include "AccountDetails.h"

class MainMenu {
private:
    PurchaseHistory history;
    MLTopUpSystem mlTopUp;
    WRTopUpSystem wrTopUp;
    HOKTopUpSystem hokTopUp;
    AccountDetails account;
    std::string currentUsername;

    void displayPurchaseHistory() {
        history.run(currentUsername);
    }

    void displayAccountDetails() {
        account.display();
    }

    // Register / Login screen
    bool loginScreen(LoginAccount& who) {
        while (true) {
            std::cout << "\n======== WELCOME ========" << std::endl;
            std::cout << "1. Register" << std::endl;
            std::cout << "2. Login" << std::endl;
            std::cout << "3. Forgot Password" << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "=========================" << std::endl;
            std::cout << "Choose: ";

            std::string choice;

            if (!std::getline(std::cin, choice)) {
                return false;
            }

            if (choice == "1") {
                registerLogin();
            }
            else if (choice == "2") {
                if (checkLogin(who)) {
                    return true;
                }
            }
            else if (choice == "3") {
                forgotPassword();
            }
            else if (choice == "4") {
                return false;
            }
            else {
                std::cout << "Invalid choice.\n";
            }
        }
    }

    // Linear Search for games
    void searchGames() {
        std::string games[] = {
            "Mobile Legends",
            "Wild Rift",
            "Honor of Kings"
        };

        std::string search;
        bool found = false;

        std::cin.ignore(10000, '\n');

        std::cout << "\n======== SEARCH GAME ========" << std::endl;
        std::cout << "Enter game name to search: ";
        std::getline(std::cin, search);

        for (char& c : search) {
            c = static_cast<char>(
                std::tolower(static_cast<unsigned char>(c))
            );
        }

        for (int i = 0; i < 3; i++) {
            std::string gameName = games[i];

            for (char& c : gameName) {
                c = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(c))
                );
            }

            if (!search.empty() &&
                gameName.find(search) != std::string::npos) {

                std::cout << "\nGame found: " << games[i] << std::endl;
                found = true;

                std::cout << "\nOpening game top-up menu..." << std::endl;

                if (i == 0) {
                    mlTopUp.run(currentUsername);
                }
                else if (i == 1) {
                    wrTopUp.run(currentUsername);
                }
                else if (i == 2) {
                    hokTopUp.run(currentUsername);
                }

                break;
            }
        }

        if (!found) {
            std::cout << "\nNo matching game found." << std::endl;
        }
    }

    // Top-Up Menu
    void runTopUpMenu() {
        int choice = 0;

        while (true) {
            std::cout << "\n======== TOP-UP MENU ========" << std::endl;
            std::cout << "1. Mobile Legends (MLBB)" << std::endl;
            std::cout << "2. Wild Rift (WR)" << std::endl;
            std::cout << "3. Honor of Kings (HOK)" << std::endl;
            std::cout << "4. Search Game" << std::endl;
            std::cout << "0. Back to Main Menu" << std::endl;
            std::cout << "=============================" << std::endl;
            std::cout << "Select an option: ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');

                std::cout << "\nInvalid input." << std::endl;
                continue;
            }

            if (choice == 1) {
                mlTopUp.run(currentUsername);
            }
            else if (choice == 2) {
                wrTopUp.run(currentUsername);
            }
            else if (choice == 3) {
                hokTopUp.run(currentUsername);
            }
            else if (choice == 4) {
                searchGames();
            }
            else if (choice == 0) {
                break;
            }
            else {
                std::cout << "\nInvalid choice." << std::endl;
            }
        }
    }

public:
    MainMenu()
        : mlTopUp(history),
          wrTopUp(history),
          hokTopUp(history),
          account(history)
    {
    }

    void displayMenu() {
        std::cout << "\n ------------- " << std::endl;
        std::cout << "              MAIN MENU              " << std::endl;
        std::cout << "\n";
        std::cout << "1. Top-up Games" << std::endl;
        std::cout << "2. Purchase History" << std::endl;
        std::cout << "3. Account Details" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "-----------------" << std::endl;
    }

    void run() {
        LoginAccount who;

        if (!loginScreen(who)) {
            std::cout << "\nExiting application. Thank you!" << std::endl;
            return;
        }

        currentUsername = who.username;
        account.setDetails(currentUsername);

        int choice = 0;

        while (true) {
            displayMenu();
            std::cout << "Enter your choice (1-4): ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');

                std::cout << "\nInvalid input. Enter a valid number." << std::endl;
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
                    std::cout << "\nExiting application. Thank you!" << std::endl;
                    return;

                default:
                    std::cout << "\nInvalid choice. Only select an option between 1 - 4." << std::endl;
                    break;
            }
        }
    }
};

#endif