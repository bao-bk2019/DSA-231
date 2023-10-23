#include<iostream>
#include<stdio.h>
#include<queue>
using namespace std;
class Node {
public:
    int data;
    Node* left;
    Node* right;
    
    Node(const int& data) { this->data = data; }
};
class BinaryTree {
private:
        Node* root;
    
protected:
        int getSizeRec(Node *node);
        int countTwoChildrenNodesRec(Node *node);
        int getHeightRec(Node *node);
        Node *maxNodeRec(Node *&node);
        bool addRec(Node *&node, const int &value);
        bool removeRec(Node *&node, const int &value);

        

    public:
        BinaryTree()
        {
            this->root = NULL;
	}

        int getSize();
        int countTwoChildrenNodes();
        int getHeight();



        Node *maxNode();
        void levelOrderTraverse();
        bool add(const int &value);
        bool remove(const int &value);
};

int BinaryTree::getSizeRec(Node *node)
{
    if (node == NULL) return 0;
	return 1 + getSizeRec(node->left) + getSizeRec(node->right);
}
int BinaryTree::getSize()
{
   return getSizeRec(this->root);
}

int BinaryTree::countTwoChildrenNodesRec(Node *node)
{
    if (node == NULL) return 0;
    if (node->left == NULL) return countTwoChildrenNodesRec(node->right);
    if (node->right == NULL) return countTwoChildrenNodesRec(node->left);
    return 1 + countTwoChildrenNodesRec(node->left) + countTwoChildrenNodesRec(node->right);
}


int BinaryTree::countTwoChildrenNodes()
{
    return countTwoChildrenNodesRec(this->root);
}

int BinaryTree::getHeightRec(Node *node)
{
	if (node == nullptr)
	    return 0;
    else{
        int left = getHeightRec(node->left);
        int right = getHeightRec(node->right);
        return left > right ? 1 + left : 1 + right;
    }
}

int BinaryTree::getHeight()
{
	return getHeightRec(this->root);
}
Node* BinaryTree::maxNodeRec(Node *&node)
{
    if (node == nullptr) return nullptr;
    Node* left = maxNodeRec(node->left);
    Node* right = maxNodeRec(node->right);
    Node* maxNode = node;
    if(left && left->data > maxNode ->data) maxNode = left;
    if(right && right->data > maxNode->data) maxNode = right;
    return maxNode;
}


Node* BinaryTree::maxNode()
{
    return maxNodeRec(this->root);
}
void BinaryTree::levelOrderTraverse()
{
    Node* currentNode=this->root;
    queue<Node*> list;
    while (currentNode!=NULL) {
        cout << currentNode->data << ' ';
        if (currentNode->left!=NULL) {
            list.push(currentNode->left);
        }
        if (currentNode->right!=NULL) {
            list.push(currentNode->right);
        }
        if (!list.empty()) {
            currentNode=list.front();
            list.pop();
        } else{
            currentNode=NULL;
        }
    }	
}
bool BinaryTree::addRec(Node *&node, const int &value)
{
	if (node==NULL) {
       Node* temp = new Node(value);
        node = temp;
        return true;
    }
    if (value > node->data) {
        addRec(node->right, value);
    } else {
        addRec(node->left, value);
    }
    return false;
}

bool BinaryTree::add(const int &value)
{
	return addRec(this->root, value);
}
bool BinaryTree::removeRec(Node *&node, const int &value)
{
	if (node == NULL) {//node is null
        return false;
    }
    if (value < node->data) { //recursive
        return removeRec(node->left, value);
    } else if (value > node->data) //recursive
        return removeRec(node->right, value);
            else{ //find node have data is the same
                if (node->left == NULL) { //have 1 child
                    node = node->right;
                    return true;
                } else if (node->right == NULL){ // have 1 child
                    node = node->left;
                    return true;
                        }
                    // have 2 or no child
                
                Node *curr = node->left;
                while (curr != NULL && curr->right !=NULL ) {
                    curr = curr->right;
                }
                 //this is smallest leaf
                node->data = curr->data;
                removeRec(node->left, curr->data);
                return true;
            }
}

bool BinaryTree::remove(const int &value)
{
	return removeRec(this->root, value);
}