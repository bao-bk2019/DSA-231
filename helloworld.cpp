#include <iostream>
#include <string.h>
using namespace std;

int power(int base, int exponent) {
    if (exponent == 0) {
        return 1;
    } else {
        return base * power(base, exponent - 1);
    }
}

int charToInt(char c) {
    return c - '0';
}

int myArrayToIntHelper(char* str, int n, int index) {
    if (index == n - 1) {
        return charToInt(str[index]);
    } else {
        int digit = charToInt(str[index]);
        int remainingValue = myArrayToIntHelper(str, n, index + 1);
        return digit * power(10, n - index - 1) + remainingValue;
    }
}

int myArrayToInt(char* str, int n) {
    return myArrayToIntHelper(str, n, 0);
}

int main() {
    char str[] = "12345";
    int result = myArrayToInt(str, strlen(str));
    cout << "Result: " << result << endl;
    return 0;
}
