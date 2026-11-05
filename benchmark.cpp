#include <iostream>
#include <chrono>
#include <cstdlib> 

using namespace std;
using namespace std::chrono;

struct Node {
    int price;
    Node* next;
    Node(int p) : price(p), next(nullptr) {}
};

Node* merge(Node* left, Node* right, bool ascending) {
    if (!left) return right;
    if (!right) return left;
    Node* result = nullptr;
    bool takeLeft = ascending ? (left->price <= right->price) : (left->price >= right->price);

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

void clearList(Node* node) {
    while (node != nullptr) {
        Node* temp = node;
        node = node->next;
        delete temp;
    }
}

int linearSearch(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearchLowerBound(const int arr[], int size, int target) {
    int low = 0, high = size;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}


// Benchmarking the algorithms

int main() {
    int sizes[] = {100, 1000, 10000, 100000};
    int repetitions = 5;

    cout.precision(6);

    cout << "Benchmarking your specific algorithms...\n\n";
    cout << "Size(n)\t\tMerge Sort(ms)\t\tLinear Search(ms)\tBinary Search(ms)\n";
    cout << "---------------------------------------------------------------------------------\n";

    for (int i = 0; i < 4; i++) {
        int n = sizes[i];
        double totalTimeMerge = 0;
        double totalTimeLinear = 0;
        double totalTimeBinary = 0;

        for (int r = 0; r < repetitions; r++) {
            
            int* data = new int[n];
            for (int j = 0; j < n; j++) {
                data[j] = rand() % 1000000;
            }

    
            Node* head = new Node(data[0]);
            Node* current = head;
            for (int j = 1; j < n; j++) {
                current->next = new Node(data[j]);
                current = current->next;
            }

            auto start = high_resolution_clock::now();
            head = mergeSort(head, true); // Ascending
            auto end = high_resolution_clock::now();
            totalTimeMerge += duration<double, milli>(end - start).count();
            
            current = head;
            for (int j = 0; j < n; j++) {
                data[j] = current->price;
                current = current->next;
            }
            clearList(head);

            int target = data[n - 1]; 

            start = high_resolution_clock::now();
            for(int k = 0; k < 1000; k++) {
                linearSearch(data, n, target);
            }
            end = high_resolution_clock::now();
            totalTimeLinear += (duration<double, milli>(end - start).count() / 1000.0);

            start = high_resolution_clock::now();
            for(int k = 0; k < 1000; k++) {
                binarySearchLowerBound(data, n, target);
            }
            end = high_resolution_clock::now();
            totalTimeBinary += (duration<double, milli>(end - start).count() / 1000.0);

            delete[] data;
        }

        //results
        cout << n << "\t\t" 
             << (totalTimeMerge / repetitions) << "\t\t" 
             << (totalTimeLinear / repetitions) << "\t\t" 
             << (totalTimeBinary / repetitions) << "\n";
    }

    return 0;
}