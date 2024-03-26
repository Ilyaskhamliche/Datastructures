#include <iostream>
#include <stack>
#include <string>

using namespace std;

int binaryToDecimal(string binary) {
    int decimal = 0;
    int base = 1;
    stack<int> binaryStack;

    // Push binary digits onto the stack
    for (int i = binary.length() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            binaryStack.push(base);
        }
        base *= 2;
    }

    // Calculate decimal value by popping from the stack
    while (!binaryStack.empty()) {
        decimal += binaryStack.top();
        binaryStack.pop();
    }

    return decimal;
}

int main() {
    string binary;
    cout << "Enter a binary number: ";
    cin >> binary;

    int decimal = binaryToDecimal(binary);
    cout << "The decimal equivalent is: " << decimal << endl;

    return 0;
}
