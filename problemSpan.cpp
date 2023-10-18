#include <iostream>
#include <vector>
#include <stack>

using namespace std;


vector<int> stock_span(const vector<int>& ns) {
    vector<int> span(ns.size(), 1); // Initialize span array with 1 as each element itself is a span of 1
    stack<int> st; // Stack to store indices of elements

    for (size_t i = 0; i < ns.size(); ++i) {
        // Pop elements from the stack while the stack is not empty and the current element is greater than the top element's price
        while (!st.empty() && ns[i] >= ns[st.top()]) {
            st.pop();
        }

        // If the stack is not empty, calculate the span using the difference of indices
        if (!st.empty()) {
            span[i] = i - st.top();
            
        }else{
        span[i] = i +1;
        }
         // Push the current index onto the stack
        st.push(i);
       
    }

    return span;

}
int main(){
    vector<int> input1 = { 100, 110, 120, 130, 140, 150};
    vector<int> input2 = {10, 4, 5, 90, 120, 80};
    input1 = stock_span(input1);
    input2 = stock_span(input2);
    for (size_t i = 0; i < input1.size(); i++)
    {
        cout << input1[i] << ' ';
    }
    cout << endl;

    input2 = stock_span(input2);
    for (size_t i = 0; i < input2.size(); i++)
    {
        cout << input2[i] << ' ';
    }
    return 0;
}