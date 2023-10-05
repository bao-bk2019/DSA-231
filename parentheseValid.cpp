#include<iostream>
#include<stack>
using namespace std;
bool isValidParentheses (string s){
    /*TODO*/
    int start = 0;
    stack<char> p;
    for (int i=start; i < s.length(); i++)
    {   
        if(s[i] == '[' || s[i] == '('){
            p.push(s[i]);
        }
        else break;
        start++;
    }
    for (int i=start; i < s.length(); i++)
    {   
        if(s[i] == '[' || s[i] == '('){
            return false;
        }
        else {
            if(p.empty()) return false;
            if (((s[i] == ')') && p.top() == '(') || ((s[i] == ']') && p.top() == '['))
            {
                p.pop();
            }else return false;
            
        }
    }
    return true;
    
}
int main(){
    string s = "[([[[[]]]])]";
    if (isValidParentheses(s))
    {
        cout<< "true";
    }else cout<< "false";
    return 0;
    
}
