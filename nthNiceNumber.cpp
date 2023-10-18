#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long nthNiceNumber(int n) {
    if (n == 1) {
        return 2; // The first nice number is 2
    }
    if (n == 2)
        return 5;

    queue<long long> q;
    q.push(2);
    q.push(5);
    while (true) {
        long long current = q.front();
        q.pop();
        
        if (--n == 0) {
            return current;
        }

        // Generate the next nice numbers by appending '2' and '5'
        q.push(current * 10 + 2);
        q.push(current * 10 + 5);
    }
}

int main() {
    int n =5;
    
    long long result = nthNiceNumber(n);
    cout << "The " << n << "th nice number is: " << result << endl;
    
    return 0;
}
