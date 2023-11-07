#include<unordered_map>
#include<iostream>
using namespace std;
struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};
/*
struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};
*/

ListNode* reverse(ListNode* head, int a, int b) {
    ListNode *curr = head, *prev = nullptr; 
    // prev points to the node before mth node 
    int i; 
    for (i = 1; i < a; i++) { 
        prev = curr; 
        curr = curr->right; 
    } 
    // This pointer stores the pointer to the head of the 
    // reversed linkedlist 
    ListNode* rtail = curr; 
    // This pointer stores the pointer to the tail of the 
    // reversed linkedlist 
    ListNode* rhead = nullptr; 
    // Now reverse the linked list from m to n nodes 
    while (i <= b) { 
        ListNode* next = curr->right; 
        curr->right = rhead; 
        rhead = curr; 
        curr = next; 
        i++; 
    } 
    // if prev is not null it means that some of the nodes 
    // exits before m  or we can say m!=1 
    if (prev != nullptr) 
        prev->right = rhead; 
    else
        head = rhead; 
    // at this point curr will point to the next of nth 
    // node where we will connect the tail of the reversed 
    // linked list 
    rtail->right = curr; 
    // at the end return the new head. 
    return head; 
}
int main(){
    int size;
    cin >> size;
    int* list = new int[size];
    for(int i = 0; i < size; i++) {
        cin >> list[i];
    }
    int a, b;
    cin >> a >> b;
    unordered_map<ListNode*, int> nodeValue;
    ListNode* head = init(list, size, nodeValue);
    ListNode* reversed = reverse(head, a, b);
    try {
        printList(reversed, nodeValue);
    }
    catch(char const* err) {
        cout << err << '\n';
    }
    freeMem(head);
    delete[] list;
}