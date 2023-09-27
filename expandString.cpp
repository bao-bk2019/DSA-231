#include <iostream>
#include <string>

std::string expand(std::string s, size_t& index) {
    if (index >= s.length()) {
        return ""; // Base case: if we're at the end of the string, return an empty string.
    }

    std::string result;

    if (std::isdigit(s[index])) {
        int num = s[index++] - '0';
        while (std::isdigit(s[index])) {
            num = num * 10 + (s[index++] - '0');
        }

        // Find the corresponding closing parenthesis
        size_t closingParenthesis = index;
        int openParenthesisCount = 0;
        while (closingParenthesis < s.length()) {
            if (s[closingParenthesis] == '(') {
                openParenthesisCount++;
            } else if (s[closingParenthesis] == ')') {
                if (openParenthesisCount == 0) {
                    break;
                }
                openParenthesisCount--;
            }
            closingParenthesis++;
        }

        // Recursively expand the substring inside the parentheses
        std::string expandedSubstring = expand(s, index);

        // Append the expanded substring 'num' times to the result
        for (int i = 0; i < num; i++) {
            result += expandedSubstring;
        }

        // Move the index past the closing parenthesis
        index = closingParenthesis;
    } else if (s[index] == ')') {
        // Return an empty string when a closing parenthesis is encountered
        index++;
    } else {
        // Append non-digit characters to the result
        result += s[index++];
    }

    // Continue processing the rest of the string recursively
    return result + expand(s, index);
}

std::string expand(std::string s) {
    size_t index = 0;
    return expand(s, index);
}

int main() {
    std::string input1 = "2(ab3(cde)x)";
    std::string input2 = "2(x0Có)3(z)";

    std::string result1 = expand(input1);
    std::string result2 = expand(input2);

    std::cout << "Result 1: " << result1 << std::endl; // Output: "abcdecdecdexabcdecdecdex"
    std::cout << "Result 2: " << result2 << std::endl; // Output: "xxzzz"

    return 0;
}
