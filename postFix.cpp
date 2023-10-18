#include <stack>
#include <iostream>
#include <cctype> // for isdigit
#include <string>

using namespace std;

int extractNumber(const string& expr, size_t& index) {
    int number = 0;
    while (index < expr.length() && isdigit(expr[index])) {
        number = number * 10 + (expr[index] - '0');
        index++;
    }
    return number;
}

int evaluatePostfix(string expr) {
    stack<int> st;

    size_t index = 0;
    while (index < expr.length()) {
        if (isdigit(expr[index])) {
            int number = extractNumber(expr, index);
            st.push(number);
        } else if (expr[index] == ' ') {
            index++; // skip whitespace
        } else {
            int val1 = st.top();
            st.pop();
            int val2 = st.top();
            st.pop();
            if (expr[index] == '+') {
                st.push(val2 + val1);
            } else if (expr[index] == '-') {
                st.push(val2 - val1);
            } else if (expr[index] == '*') {
                st.push(val2 * val1);
            } else if (expr[index] == '/') {
                st.push(val2 / val1);
            }
            index++;
        }
    }
    return st.top();
}

int main() {
    cout << evaluatePostfix("100 200 + 2 / 5 * 7 +"); // Output: 57
    return 0;
}
