
#ifndef MLTOPUP_H
#define MLTOPUP_H

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include "PurchaseHistory.h"

class MLTopUpSystem {
private:
    int diamondPackages[6] = {86, 172, 257, 344, 706, 1412};
    int packagePrices[6] = {49, 99, 149, 199, 399, 799};

    int playerID = 0;
    int zoneID = 0;

    struct Node {
        int diamonds;
        int price;
        Node* next;

        Node(int d, int p)
            : diamonds(d), price(p), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    PurchaseHistory& history;   // shared with the Main Menu

    // Merge two sorted linked lists.
    Node* merge(Node* left, Node* right, bool ascending) {
        if (!left)
            return right;

        if (!right)
            return left;

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

    // Sort a linked list using Merge Sort.
    Node* mergeSort(Node* node, bool ascending) {
        if (node == nullptr || node->next == nullptr)
            return node;

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

    // Sort the actual package arrays using Merge Sort.
    void sortPackages(bool ascending) {
        Node* sortedList = nullptr;
        Node* sortedTail = nullptr;

        // Copy the current packages into a temporary linked list.
        for (int i = 0; i < 6; i++) {
            Node* newNode = new Node(
                diamondPackages[i],
                packagePrices[i]
            );

            if (sortedList == nullptr) {
                sortedList = newNode;
                sortedTail = newNode;
            } else {
                sortedTail->next = newNode;
                sortedTail = newNode;
            }
        }

        // Perform Merge Sort.
        sortedList = mergeSort(sortedList, ascending);

        // Copy the sorted results back into the original arrays.
        Node* current = sortedList;

        for (int i = 0; i < 6; i++) {
            diamondPackages[i] = current->diamonds;
            packagePrices[i] = current->price;

            current = current->next;
        }

        // Free the temporary linked list.
        clearList(sortedList);

        std::cout << "\nPackages sorted by price: "
                  << (ascending
                      ? "Lowest to Highest\n"
                      : "Highest to Lowest\n");

        displayPackages();
    }

    // Delete a temporary linked list.
    void clearList(Node* node) {
        while (node != nullptr) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }

    void addToCart(int index) {
        Node* newNode = new Node(
            diamondPackages[index],
            packagePrices[index]
        );

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        std::cout << "\nAdded "
                  << diamondPackages[index]
                  << " diamonds to your cart." << std::endl;
    }

    void displayCart() {
        if (head == nullptr) {
            std::cout << "\nYour cart is empty." << std::endl;
            return;
        }

        int total = 0;
        int itemNumber = 1;

        std::cout << "\n========== YOUR CART ==========" << std::endl;
        std::cout << std::left
                  << std::setw(8) << "Item"
                  << std::setw(18) << "Diamonds"
                  << std::setw(12) << "Price" << std::endl;

        std::cout << "--------------------------------------" << std::endl;

        Node* current = head;

        while (current != nullptr) {
            std::cout << std::left << std::setw(8) << itemNumber << std::setw(18) << current->diamonds << "PHP " << std::fixed << current->price << std::endl;

            total += current->price;
            current = current->next;
            itemNumber++;
        }

        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Total: PHP " << total << std::endl;
    }

    void removeFromCart() {
        if (head == nullptr) {
            std::cout << "\nYour cart is empty." << std::endl;
            return;
        }

        displayCart();

        int position;
        std::cout << "\nEnter the item number to remove: ";

        if (!(std::cin >> position)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input." << std::endl;
            return;
        }

        if (position < 1) {
            std::cout << "Invalid item number." << std::endl;
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

        if (current == tail)
            tail = previous;

        std::cout << current->diamonds
                  << " diamonds removed from your cart." << std::endl;

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

        std::cout << "\nEnter your Mobile Legends Player ID: ";
        if (!(std::cin >> playerID)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid Player ID." << std::endl;
            return;
        }

        std::cout << "Enter your Zone ID: ";
        if (!(std::cin >> zoneID)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid Zone ID.\n";
            return;
        }

        int total = 0;
        int totalDiamonds = 0;

        Node* current = head;

        while (current != nullptr) {
            total += current->price;
            totalDiamonds += current->diamonds;
            current = current->next;
        }

       
        std::cout << "\n========== RECEIPT ==========\n";

        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);

        if (localTime != nullptr) {
            char dateBuffer[50];

            std::strftime(dateBuffer, sizeof(dateBuffer), "%B %d, %Y", localTime);

            std::cout << "Date: "<< dateBuffer << std::endl;
        }

        std::cout << "Player ID: " << playerID << std::endl;
        std::cout << "Zone ID: " << zoneID << std::endl;
        std::cout << "Total Diamonds: " << totalDiamonds << std::endl;
        std::cout << "Total Amount: PHP " << total << std::endl;
        std::cout << "Status: Sent" << std::endl;
        std::cout << "===============================" << std::endl;

        // Save this purchase to Purchase History.
        int dateKey = 0;
        if (localTime != nullptr)
            dateKey = (localTime->tm_year + 1900) * 10000
                    + (localTime->tm_mon + 1) * 100
                    + localTime->tm_mday;
        history.addTransaction(dateKey, playerID, zoneID, totalDiamonds, total);


        clearCart();
    }

public:
    MLTopUpSystem(PurchaseHistory& h) : head(nullptr), tail(nullptr), history(h) {}

    MLTopUpSystem(const MLTopUpSystem&) = delete;
    MLTopUpSystem& operator=(const MLTopUpSystem&) = delete;

    ~MLTopUpSystem() {
        clearCart();
    }

    void displayPackages() {
        std::cout << "\n======= MOBILE LEGENDS TOP-UP =======" << std::endl;
        std::cout << std::left
                  << std::setw(8) << "Option"
                  << std::setw(18) << "Diamonds"
                  << "Price (PHP)" << std::endl;

        std::cout << "-------------------------------------" << std::endl;

        for (int i = 0; i < 6; i++) {
            std::cout << std::left << std::setw(8) << i + 1 << std::setw(18) << diamondPackages[i] << std::fixed << packagePrices[i] << '\n';
        }

        std::cout << "-------------------------------------" << std::endl;
        std::cout << "7. View Cart" << std::endl;
        std::cout << "8. Checkout" << std::endl;
        std::cout << "9. Remove Item from Cart" << std::endl;
        std::cout << "10. Sort Packages: Lowest to Highest Price" << std::endl;
        std::cout << "11. Sort Packages: Highest to Lowest Price" << std::endl;
        std::cout << "0. Exit" << std::endl;
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
                std::cout << "Invalid input. Please enter a number." << std::endl;
                continue;
            }

            if (choice >= 1 && choice <= 6) {
                addToCart(choice - 1);
            } else {
                switch (choice) {
                    case 7:
                        displayCart();
                        break;

                    case 8:
                        checkout();
                        break;

                    case 9:
                        removeFromCart();
                        break;

                    case 10:
                        sortPackages(true);
                        break;

                    case 11:
                        sortPackages(false);
                        break;

                    case 0:
                        std::cout << "\nThank you for using ML Top-Up!" << std::endl;
                        return;

                    default:
                        std::cout << "\nInvalid choice. Try again." << std::endl;
                }
            }
        }
    }
};

#endif
