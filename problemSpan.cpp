#include <iostream>
#include <vector>
#include <stack>

using namespace std;


vector<int> stock_span(const vector<int>& ns) {
    vector<int> span(ns.size(), 1); // Initialize span array with 1 as each element itself is a span of 1
    stack<int> st; // Stack to store indices of elements

    for (size_t i = 0; i < ns.size(); ++i) {
        // Pop elements from the stack while the stack is not empty and the current element is greater than the top element's price
        while (!st.empty() && ns[i] > ns[st.top()]) {
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
    vector<int> input1 = { 64,	40,	21,	52,	9,	57,	79,	4,	16,	57,
36,	26,	17,	42,	58,	25,	62,	70,	62,	82,
33, 34,	43,	64,	48,	75,	9,	18,	22,	84,
60,	12,	63,	3,	24,	70,	37,	33,	89,	89,
4,	87,	87,	68,	72,	14,	40,	60,	10,	87,
80,	73,	43,	57,	17,	64,	71,	21,	37	,49,
19,	77,	38,	33,	78,	34,	77,	73,	80,	44,
99,	83,	65,	5,	5,	4,	59,	80,	60,	89,
82,	27,	27,	51,	23,	65,	85,	92,	47,	79,
58,	84,	30,	98,	1,	27,	57,	67,	11,	68};
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