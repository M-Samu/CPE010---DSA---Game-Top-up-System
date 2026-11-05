#ifndef WRTOPUP_H
#define WRTOPUP_H

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>
#include "PurchaseHistory.h"
#include "payMethod.h"

class WRTopUpSystem {
private:
    int coresPackages[6] = {425, 1000, 1850, 3275, 4800, 10000};
    int packagePrices[6] = {200, 449, 819, 1430, 2050, 4090};

    int playerID = 0;

    struct Node {
        int cores;
        int price;
        Node* next;

        Node(int d, int p)
            : cores(d), price(p), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    PurchaseHistory& history;   // shared with the Main Menu

    Node* merge(Node* left, Node* right, bool ascending) {
        if (!left) return right;
        if (!right) return left;
        Node* result = nullptr;
        bool takeLeft;
        if (ascending)
            takeLeft = left->price <= right->price;
        else
            takeLeft = left->price >= right->price;

        if (takeLeft) {
            result = left;
            result->next = merge(left->next, right, ascending);
        } else {
            result = right;
            result->next = merge(left, right->next, ascending);
        }
        return result;
    }

    Node* mergeSort(Node* node, bool ascending) {
        if (node == nullptr || node->next == nullptr) return node;
        Node* slow = node;
        Node* fast = node->next;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* right = slow->next;
        slow->next = nullptr;
        Node* leftSorted = mergeSort(node, ascending);
        Node* rightSorted = mergeSort(right, ascending);
        return merge(leftSorted, rightSorted, ascending);
    }

    void sortPackages(bool ascending) {
        Node* sortedList = nullptr;
        Node* sortedTail = nullptr;
        for (int i = 0; i < 6; i++) {
            Node* newNode = new Node(coresPackages[i], packagePrices[i]);
            if (sortedList == nullptr) {
                sortedList = newNode;
                sortedTail = newNode;
            } else {
                sortedTail->next = newNode;
                sortedTail = newNode;
            }
        }
        sortedList = mergeSort(sortedList, ascending);
        Node* current = sortedList;
        for (int i = 0; i < 6; i++) {
            coresPackages[i] = current->cores;
            packagePrices[i] = current->price;
            current = current->next;
        }
        clearList(sortedList);
        std::cout << "\nPackages sorted by price: "
                  << (ascending ? "Lowest to Highest\n" : "Highest to Lowest\n");
        displayPackages();
    }

    void clearList(Node* node) {
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }

    void addToCart(int index) {
        Node* newNode = new Node(coresPackages[index], packagePrices[index]);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        std::cout << "\nAdded " << coresPackages[index] << " cores to your cart.\n";
    }

    void displayCart() {
        if (head == nullptr) {
            std::cout << "\nYour cart is empty.\n";
            return;
        }
        int total = 0;
        int itemNumber = 1;
        std::cout << "\n========== YOUR CART ==========\n";
        std::cout << std::left << std::setw(8) << "Item"
                  << std::setw(18) << "Cores"
                  << std::setw(12) << "Price\n";
        std::cout << "--------------------------------------\n";
        Node* current = head;
        while (current != nullptr) {
            std::cout << std::left << std::setw(8) << itemNumber
                      << std::setw(18) << current->cores
                      << "PHP " << std::fixed << current->price << '\n';
            total += current->price;
            current = current->next;
            itemNumber++;
        }
        std::cout << "--------------------------------------\n";
        std::cout << "Total: PHP " << total << '\n';
    }

    void removeFromCart() {
        if (head == nullptr) {
            std::cout << "\nYour cart is empty.\n";
            return;
        }
        displayCart();
        int position;
        std::cout << "\nEnter the item number to remove: ";
        if (!(std::cin >> position)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n";
            return;
        }
        if (position < 1) {
            std::cout << "Invalid item number.\n";
            return;
        }
        Node* current = head;
        Node* previous = nullptr;
        int currentPosition = 1;
        while (current != nullptr && currentPosition < position) {
            previous = current;
            current = current->next;
            currentPosition++;
        }
        if (current == nullptr) {
            std::cout << "Item number not found.\n";
            return;
        }
        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        if (current == tail) tail = previous;
        std::cout << current->cores << " cores removed from your cart.\n";
        delete current;
    }

    void clearCart() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void checkout() {
        if (head == nullptr) {
            std::cout << "\nYour cart is empty. Add a package first.\n";
            return;
        }
        displayCart();
        char confirm;
        std::cout << "\nProceed to checkout? (Y/N): ";
        std::cin >> confirm;
        if (confirm != 'Y' && confirm != 'y') {
            std::cout << "Checkout cancelled.\n";
            return;
        }

        std::cout << "\\nEnter your Wild Rift Player ID: ";
        if (!(std::cin >> playerID)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid Player ID.\\n";
            return;
        }

        int total = 0;
        int totalCores = 0;
        Node* current = head;
        while (current != nullptr) {
            total += current->price;
            totalCores += current->cores;
            current = current->next;
        }

        // --- Execute Payment Method ---
        double finalTotal = PayMethod::processPayment(total);
        int finalTotalInt = static_cast<int>(std::round(finalTotal));

        std::cout << "\n========== RECEIPT ==========\n";
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        if (localTime != nullptr) {
            char dateBuffer[50];
            std::strftime(dateBuffer, sizeof(dateBuffer), "%B %d, %Y", localTime);
            std::cout << "Date: "<< dateBuffer << std::endl;
        }
        std::cout << "Player ID: " << playerID << std::endl;
        std::cout << "Total Cores: " << totalCores << std::endl;
        std::cout << "Total Amount: PHP " << finalTotalInt << std::endl;
        std::cout << "Status: Sent" << std::endl;
        std::cout << "===============================" << std::endl;

        int dateKey = 0;
        if (localTime != nullptr)
            dateKey = (localTime->tm_year + 1900) * 10000 + (localTime->tm_mon + 1) * 100 + localTime->tm_mday;
            
        history.addTransaction(dateKey, playerID, totalCores, finalTotalInt);
        clearCart();
    }

public:
    WRTopUpSystem(PurchaseHistory& h) : head(nullptr), tail(nullptr), history(h) {}
    WRTopUpSystem(const WRTopUpSystem&) = delete;
    WRTopUpSystem& operator=(const WRTopUpSystem&) = delete;
    ~WRTopUpSystem() { clearCart(); }

    void displayPackages() {
        std::cout << "\n======= LEAGUE OF LEGENDS: WILD RIFT TOP-UP =======" << std::endl;
        std::cout << std::left << std::setw(8) << "Option" << std::setw(18) << "Cores" << "Price (PHP)" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        for (int i = 0; i < 6; i++) {
            std::cout << std::left << std::setw(8) << i + 1 << std::setw(18) << coresPackages[i] << std::fixed << packagePrices[i] << '\n';
        }
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "7. View Cart\n8. Checkout\n9. Remove Item from Cart\n";
        std::cout << "10. Sort Packages: Lowest to Highest Price\n";
        std::cout << "11. Sort Packages: Highest to Lowest Price\n";
        std::cout << "0. Exit\n";
        std::cout << "=====================================" << std::endl;
    }

    void run() {
        int choice;
        while (true) {
            displayPackages();
            std::cout << "\nEnter your choice: ";
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a number.\\n";
                continue;
            }
            if (choice >= 1 && choice <= 6) {
                addToCart(choice - 1);
            } else {
                switch (choice) {
                    case 7: displayCart(); break;
                    case 8: checkout(); break;
                    case 9: removeFromCart(); break;
                    case 10: sortPackages(true); break;
                    case 11: sortPackages(false); break;
                    case 0: std::cout << "\nThank you for using ML Top-Up!\n"; return;
                    default: std::cout << "\nInvalid choice. Try again.\n";
                }
            }
        }
    }
};
#endif