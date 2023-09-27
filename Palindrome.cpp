#include <iostream>
#include <string>

using namespace std;


void removeSpacesRecursive( string& str, int index = 0) {
    if (index == str.length()) {
        // Base case: We've reached the end of the string
        return;
    }

    if (str[index] == ' ') {
        // If the current character is a space, remove it
        str.erase(index, 1);
    }
        // If it's not a space, move on to the next character
    removeSpacesRecursive(str, index + 1);
    
}

bool isPalindromeHelper( string& str, int left, int right) {
    

    if (left >= right) {
        return true; // Base case: Empty string or single character is a palindrome
    }

    // Compare the characters (case-insensitive)
    if (tolower(str[left]) != tolower(str[right])) {
        return false; // Characters at left and right positions don't match, not a palindrome
    }

    // Recursively check the substring without the first and last characters
    return isPalindromeHelper(str, left + 1, right - 1);
}

bool isPalindrome( string& str) {
    removeSpacesRecursive(str,0);
    int left = 0;
    int right = str.length() - 1;
    return isPalindromeHelper(str, left, right);
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    if (isPalindrome(input)) {
        cout << input << " is a palindrome." << endl;
    } else {
        cout << input << " is not a palindrome." << endl;
    }

    return 0;
}
