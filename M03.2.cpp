#include <iostream>
#include <string>
#include "hashT.h" // Include the hashT class header file

using namespace std;

// Hash function 1: Simple modular hashing
int hashFunc1(string key, int tableSize) {
    int sum = 0;
    for (char c : key) {
        sum += static_cast<int>(c);
    }
    return sum % tableSize;
}

// Hash function 2: Horner's method
int hashFunc2(string key, int tableSize) {
    int sum = 0;
    for (char c : key) {
        sum = (sum * 31 + static_cast<int>(c)) % tableSize;
    }
    return sum;
}

// Hash function 3: Polynomial hashing
int hashFunc3(string key, int tableSize) {
    int sum = 0;
    int p = 31; // Prime number
    for (char c : key) {
        sum = (sum * p + static_cast<int>(c)) % tableSize;
    }
    return sum;
}

int main() {
    hashT<int, string> hashTable1(10, hashFunc1); // Using hash function 1
    hashT<int, string> hashTable2(10, hashFunc2); // Using hash function 2
    hashT<int, string> hashTable3(10, hashFunc3); // Using hash function 3

    // Test operations for each hash table
    hashTable1.insert(123, "Apple");
    hashTable1.insert(456, "Banana");
    hashTable1.insert(789, "Cherry");
    hashTable1.print();

    hashTable2.insert(123, "Apple");
    hashTable2.insert(456, "Banana");
    hashTable2.insert(789, "Cherry");
    hashTable2.print();

    hashTable3.insert(123, "Apple");
    hashTable3.insert(456, "Banana");
    hashTable3.insert(789, "Cherry");
    hashTable3.print();

    return 0;
}
