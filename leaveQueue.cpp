#include <iostream>
#include <queue>
#include <stack>

using namespace std;

void interleaveQueue(queue<int>& q){
    int n = q.size();
    int halfSize = n / 2;
    queue<int> qq;

    // Push the first half of the queue into a stack
    for (int i = 0; i < halfSize; ++i) {
        qq.push(q.front());
        q.pop();
    }

    // Interleave elements from the stack and the remaining queue
    while (!qq.empty()) {
        q.push(qq.front());
        qq.pop();
        q.push(q.front());
        q.pop();
    }

   
}

int main() {
    queue<int> q;
    q.push(2);
    q.push(4);
    q.push(6);
    q.push(8);
    q.push(10);
    q.push(12);
   
    interleaveQueue(q);
    while (!q.empty()) {
        cout << q.front() << ' ';
        q.pop();
    }
    cout << endl;
    return 0;
}
