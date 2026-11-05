#ifndef PURCHASEHISTORY_H
#define PURCHASEHISTORY_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdio>

// Base Transaction (for MLBB - legacy format)
struct Transaction {
    int id;
    int dateKey;
    int playerID;
    int zoneID; // -1 if not applicable
    std::string playerEmail; // Empty if not applicable
    int totalItems; // generic for diamonds, cores, tokens
    int totalAmount;
    std::string currencyName; // "Diamonds", "Cores", "Tokens"
    std::string gameName;
    std::string status;
};

class PurchaseHistory {
private:
    Transaction* records;   
    int count;
    int capacity;
    int nextID;

    void grow() {
        capacity *= 2;
        Transaction* bigger = new Transaction[capacity];
        for (int i = 0; i < count; i++)
            bigger[i] = records[i];
        delete[] records;
        records = bigger;
    }

    int lowerBound(int target) const {
        int low = 0, high = count;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (records[mid].dateKey < target)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }

    int upperBound(int target) const {
        int low = 0, high = count;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (records[mid].dateKey <= target)
                low = mid + 1;
            else
                high = mid;
        }
        return low;
    }

    static std::string formatDate(int key) {
        static const char* months[] = {"January", "February", "March", "April",
            "May", "June", "July", "August", "September", "October",
            "November", "December"};
        int y = key / 10000;
        int m = (key / 100) % 100;
        int d = key % 100;
        return std::string(months[m - 1]) + " " + std::to_string(d) + ", " + std::to_string(y);
    }

    static void printHeader() {
        std::cout << std::left
                  << std::setw(6)  << "ID"
                  << std::setw(20) << "Date"
                  << std::setw(15) << "Game"
                  << std::setw(25) << "Account (ID/Email)"
                  << std::setw(15) << "Item Count"
                  << std::setw(12) << "Amount"
                  << "Status\n";
        std::cout << "------------------------------------------------------------------------------------------------------\n";
    }

    static void printRow(const Transaction& t) {
        std::string accountStr = (t.playerEmail.empty()) 
            ? std::to_string(t.playerID) + (t.zoneID != -1 ? " (" + std::to_string(t.zoneID) + ")" : "")
            : t.playerEmail;
            
        std::string itemStr = std::to_string(t.totalItems) + " " + t.currencyName;

        std::cout << std::left
                  << std::setw(6)  << t.id
                  << std::setw(20) << formatDate(t.dateKey)
                  << std::setw(15) << t.gameName
                  << std::setw(25) << accountStr
                  << std::setw(15) << itemStr
                  << std::setw(12) << ("PHP " + std::to_string(t.totalAmount))
                  << t.status << "\n";
    }

    static int readDate(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::cin >> input;

        int y, m, d;
        if (std::sscanf(input.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
            return -1;
        if (y < 1900 || y > 9999 || m < 1 || m > 12 || d < 1 || d > 31)
            return -1;
        return y * 10000 + m * 100 + d;
    }

public:
    PurchaseHistory() : records(new Transaction[10]), count(0), capacity(10), nextID(1) {}
    PurchaseHistory(const PurchaseHistory&) = delete;
    PurchaseHistory& operator=(const PurchaseHistory&) = delete;
    ~PurchaseHistory() { delete[] records; }

    // MLBB
    void addTransaction(int dateKey, int playerID, int zoneID, int totalDiamonds, int totalAmount) {
        if (count == capacity) grow();
        int pos = count;
        while (pos > 0 && records[pos - 1].dateKey > dateKey) {
            records[pos] = records[pos - 1];
            pos--;
        }
        records[pos] = {nextID++, dateKey, playerID, zoneID, "", totalDiamonds, totalAmount, "Diamonds", "MLBB", "Sent"};
        count++;
    }

    // WR
    void addTransaction(int dateKey, int playerID, int totalCores, int totalAmount) {
        if (count == capacity) grow();
        int pos = count;
        while (pos > 0 && records[pos - 1].dateKey > dateKey) {
            records[pos] = records[pos - 1];
            pos--;
        }
        records[pos] = {nextID++, dateKey, playerID, -1, "", totalCores, totalAmount, "Cores", "Wild Rift", "Sent"};
        count++;
    }

    // HOK
    void addTransaction(int dateKey, const std::string& playerEmail, int totalTokens, int totalAmount) {
        if (count == capacity) grow();
        int pos = count;
        while (pos > 0 && records[pos - 1].dateKey > dateKey) {
            records[pos] = records[pos - 1];
            pos--;
        }
        records[pos] = {nextID++, dateKey, 0, -1, playerEmail, totalTokens, totalAmount, "Tokens", "HoK", "Sent"};
        count++;
    }

    void loadSampleData() {
        addTransaction(20260915, 123456789, 1234, 86, 49);  // MLBB
        addTransaction(20260916, 987654321, 1000, 449);     // WR
        addTransaction(20261003, "gamer@email.com", 80, 65); // HOK
    }

    void displayAll() const {
        if (count == 0) {
            std::cout << "\nNo recent transactions found...\n";
            return;
        }
        std::cout << "\n";
        printHeader();
        for (int i = 0; i < count; i++)
            printRow(records[i]);
    }

    void filterDate(int startKey, int endKey) const {
        if (startKey > endKey) {
            std::cout << "\nStart date must not be after end date.\n";
            return;
        }
        int first = lowerBound(startKey);
        int last  = upperBound(endKey);

        if (first >= last) {
            std::cout << "\nNo transactions found for that date.\n";
            return;
        }

        std::cout << "\n";
        printHeader();
        int total = 0;
        for (int i = first; i < last; i++) {
            printRow(records[i]);
            total += records[i].totalAmount;
        }
        std::cout << "------------------------------------------------------------------------------------------------------\n";
        std::cout << (last - first) << " transaction(s) | Total spent: PHP " << total << "\n";
    }

    void run() const {
        int choice = -1;
        while (choice != 0) {
            std::cout << "\n======= PURCHASE HISTORY =======\n";
            std::cout << "1. View all transactions\n";
            std::cout << "2. Filter by date\n";
            std::cout << "3. Filter by date range\n";
            std::cout << "0. Back\n";
            std::cout << "================================\n";
            std::cout << "Enter your choice: ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "\nInvalid input. Please enter a number.\n";
                choice = -1;
                continue;
            }

            if (choice == 1) {
                displayAll();
            } else if (choice == 2) {
                int d = readDate("\nEnter date (YYYY-MM-DD): ");
                if (d == -1) std::cout << "Invalid date format.\n";
                else filterDate(d, d);
            } else if (choice == 3) {
                int s = readDate("\nEnter start date (YYYY-MM-DD): ");
                int e = (s == -1) ? -1 : readDate("Enter end date (YYYY-MM-DD): ");
                if (s == -1 || e == -1) std::cout << "Invalid date format.\n";
                else filterDate(s, e);
            } else if (choice != 0) {
                std::cout << "\nInvalid choice.\n";
            }
        }
    }
};

#endif