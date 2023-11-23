#include<iostream>
#include<queue>
#include<stack>
#include<utility>
using namespace std;
class BTNode {
    public: 
        int val; 
        BTNode *left; 
        BTNode *right; 
        BTNode() {
            this->left = this->right = NULL;
        } 
        BTNode(int val) {
            this->val = val;
            this->left = this->right = NULL;
        } 
        BTNode(int val, BTNode*& left, BTNode*& right) {
            this->val = val;
            this->left = left;
            this->right = right;
        } 
};
int sumDigitPath(BTNode* root);
int main(){
    int arr[] = {-1,0,0,2,2};
    int value[] = {3,5,2,1,4};
    BTNode* root = BTNode::createTree(arr, arr + sizeof(arr)/sizeof(int), value);
    cout << sumDigitPath(root);
    return 0;
}