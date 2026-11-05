#ifndef PAYMETHOD_H
#define PAYMETHOD_H

#include <iostream>
#include <iomanip>
#include <cmath>

// --- Array Queue implementation for BNPL Installments ---
struct Installment {
    int month;
    double amount;
};

class InstallmentQueue {
private:
    static const int MAX_INSTALLMENTS = 12;
    Installment queue[MAX_INSTALLMENTS];
    int front;
    int rear;
    int count;

public:
    InstallmentQueue() : front(0), rear(-1), count(0) {}

    void enqueue(int month, double amount) {
        if (count == MAX_INSTALLMENTS) {
            std::cout << "Installment queue is full!\n";
            return;
        }
        rear = (rear + 1) % MAX_INSTALLMENTS;
        queue[rear].month = month;
        queue[rear].amount = amount;
        count++;
    }

    // Dequeues and processes each installment in FIFO order
    void processAllInstallments() {
        std::cout << "\n--- Processing BNPL Installments (FIFO Queue) ---\n";
        while (count > 0) {
            Installment current = queue[front];
            std::cout << "Paid Month " << current.month << " Installment: PHP " 
                      << std::fixed << std::setprecision(2) << current.amount << "\n";
            
            // Circularly advance front
            front = (front + 1) % MAX_INSTALLMENTS;
            count--;
        }
        std::cout << "All installments successfully scheduled and processed!\n";
        std::cout << "-------------------------------------------------\n";
    }
};

class PayMethod {
public:
    // Returns the final computed total after applying any interest
    static double processPayment(double totalAmount) {
        int choice = 0;
        while (true) {
            std::cout << "\n========== PAYMENT METHODS ==========\n";
            std::cout << "1. GCash\n";
            std::cout << "2. Maya\n";
            std::cout << "3. PayPal\n";
            std::cout << "4. Buy Now, Pay Later (BNPL)\n";
            std::cout << "=====================================\n";
            std::cout << "Select payment method (1-4): ";

            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Try again.\n";
                continue;
            }

            if (choice == 1) {
                std::cout << "\nProcessing GCash payment...\n";
                return totalAmount;
            } else if (choice == 2) {
                std::cout << "\nProcessing Maya payment...\n";
                return totalAmount;
            } else if (choice == 3) {
                std::cout << "\nProcessing PayPal payment...\n";
                return totalAmount;
            } else if (choice == 4) {
                return processPayLater(totalAmount);
            } else {
                std::cout << "Invalid choice. Please select 1 through 4.\n";
            }
        }
    }

private:
    static double processPayLater(double totalAmount) {
        int option = 0;
        double interestRate = 0.0;
        double finalAmount = totalAmount;
        int months = 1;

        while (true) {
            std::cout << "\n====== BUY NOW, PAY LATER ======\n";
            std::cout << "1. 1 Month  (0% interest)\n";
            std::cout << "2. 2 Months (1.3% interest)\n";
            std::cout << "3. 3 Months (1.3% interest)\n";
            std::cout << "================================\n";
            std::cout << "Select installment plan (1-3): ";

            if (!(std::cin >> option)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Try again.\n";
                continue;
            }

            if (option == 1) {
                months = 1;
                interestRate = 0.0;
                break;
            } else if (option == 2) {
                months = 2;
                interestRate = 0.013; // 1.3%
                break;
            } else if (option == 3) {
                months = 3;
                interestRate = 0.013; // 1.3%
                break;
            } else {
                std::cout << "Invalid option. Please select 1, 2, or 3.\n";
            }
        }

        finalAmount = totalAmount + (totalAmount * interestRate);
        double monthlyPayment = finalAmount / months;

        std::cout << "\n--- BNPL Plan Selected ---\n";
        std::cout << "Principal Amount : PHP " << std::fixed << std::setprecision(2) << totalAmount << "\n";
        std::cout << "Interest Applied : PHP " << (totalAmount * interestRate) << " (" << (interestRate * 100) << "%)\n";
        std::cout << "Total to Pay     : PHP " << finalAmount << "\n";
        std::cout << "Monthly Payment  : PHP " << monthlyPayment << " for " << months << " month(s)\n";
        
        // Use the Queue Array to process installments
        InstallmentQueue queue;
        
        // Enqueue each month's payment
        for (int i = 1; i <= months; i++) {
            queue.enqueue(i, monthlyPayment);
        }
        
        // Dequeue (FIFO) to simulate processing the payment schedule
        queue.processAllInstallments();

        return finalAmount;
    }
};

#endif