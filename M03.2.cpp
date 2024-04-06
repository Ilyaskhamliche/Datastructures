#include <iostream>
#include <string>
using namespace std;

// Hash function 1: Division method
int hashFunc1(int key, int size) {
    return key % size;
}

// Hash function 2: Multiplication method
int hashFunc2(int key, int size) {
    double A = 0.6180339887; // Constant value
    int value = static_cast<int>(size * (key * A - static_cast<int>(key * A)));
    return value;
}

// Hash function 3: Universal hashing
int hashFunc3(int key, int size, int a, int b) {
    return ((a * key + b) % size);
}

int main() {
    // Test hash function 1
    int size1 = 10;
    int key1 = 123;
    int index1 = hashFunc1(key1, size1);
    cout << "Hash function 1 (Division method): Key = " << key1 << ", Index = " << index1 << endl;

    // Test hash function 2
    int size2 = 20;
    int key2 = 456;
    int index2 = hashFunc2(key2, size2);
    cout << "Hash function 2 (Multiplication method): Key = " << key2 << ", Index = " << index2 << endl;

    // Test hash function 3
    int size3 = 15;
    int key3 = 789;
    int a = 7, b = 11;
    int index3 = hashFunc3(key3, size3, a, b);
    cout << "Hash function 3 (Universal hashing): Key = " << key3 << ", Index = " << index3 << endl;

    return 0;
}
