#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    void remove(const T &value){
        bool shorter=false, success=false;
        this->root=removeRec(this->root, value, shorter, success);
    }
    Node* removeRec(Node *&node,const int &value, bool &shorter, bool &success){
        if(node == nullptr){
            shorter = false;
            success = false;
            return nullptr;
        }
    if(value < node->data){
        node->pLeft = removeRec(node->pLeft, value, shorter, success);
        if (shorter)
            node = removeRightBalance(node, shorter);
    } else if(value > node->data){
            node->pRight = removeRec(node->pRight, value, shorter, success);
            if (shorter)
                node = removeLeftBalance(node, shorter);
        }
        // Delete node found – test for leaf node
    else{
        Node* deleteNode = node;
        if(node->pRight == nullptr){
            Node* newNode = node->pLeft;
            success = true;
            shorter = true;
            delete deleteNode;
            return newNode;
        } else if(node->pLeft == nullptr){
            Node* newNode = node->pRight;
            success = true;
            shorter = true;
            delete deleteNode;
            return newNode;
        } else {// Delete node has two subtrees
            Node* exchPtr = node->pLeft;
            while(exchPtr->pRight != nullptr){
                exchPtr = exchPtr->pRight;
            }
            node->data = exchPtr->data;
            node->pLeft = removeRec(node->pLeft, exchPtr->data, shorter, success);
            if(shorter){
                node = removeRightBalance(node, shorter);
            }
        }
        
    }
    return node;
    }
    Node* removeRightBalance(Node *&node, bool &shorter){
        if(node->balance == LH){
            node->balance = EH;
        }else if(node->balance == EH){
            node->balance = RH;
            shorter = false;
        }else{
            Node* rightTree = node->pRight;
            if(rightTree->balance == LH){
                Node* leftTree = rightTree->pLeft;
                if(leftTree->balance == LH){
                    rightTree->balance = RH;
                    node->balance = EH;
                }else if(leftTree->balance == EH){
                        node->balance = EH;
                        rightTree->balance = EH;
                }else{
                    node->balance = LH;
                    rightTree->balance = EH;
                }
                
                leftTree->balance = EH;
                node->pRight = rotateRight(rightTree);
                node = rotateLeft(node);
            }else{
                if(rightTree->balance != EH){
                    node->balance = EH;
                    rightTree->balance = EH;
                }else{
                    node->balance = RH;
                    rightTree->balance = LH;
                    shorter = false;
                }
                node = rotateLeft(node);
            }
        }
    return  node;
    }
    Node* removeLeftBalance(Node *&node, bool &shorter){
        if(node->balance == RH){
        node->balance = EH;
        }else if(node->balance == EH){
            node->balance = LH;
            shorter = false;
        }else{
            Node* leftTree = node->pLeft;
            if(leftTree->balance == RH){
                Node* rightTree = leftTree->pRight;
                if(rightTree->balance == RH){
                    rightTree->balance = LH;
                    node->balance = EH;
                }else if(rightTree->balance == EH){
                    node->balance = EH;
                    leftTree->balance = EH;
                }else{
                    node->balance = RH;
                    leftTree->balance = EH;
                }
                
                rightTree->balance = EH;
                node->pLeft = rotateLeft(leftTree);
                node = rotateRight(node);
            }else{
                if(leftTree->balance != EH){
                    node->balance = EH;
                    leftTree->balance = EH;
                }else{
                    node->balance = LH;
                    leftTree->balance = RH;
                    shorter = false;
                }
                node = rotateRight(node);
            }
        }
    
    return  node;
    }
    //Helping functions

//Helping functions
Node* rotateRight(Node *&node)
{
    Node *temp = node->pLeft;
    node->pLeft = temp->pRight;
    temp->pRight = node;
    return temp;
}


Node* rotateLeft(Node *&node)
{
    Node *temp = node->pRight;
    node->pRight = temp->pLeft;
    temp->pLeft = node;
    return temp;
}

Node* leftBalance(Node *&node)
{
    Node *leftb = node->pLeft;
    if(leftb->balance == LH) {
        node = rotateRight(node);
        node->balance = EH;
        node->pRight->balance = EH;
    }
    else {
        Node *rightb = leftb->pRight;
        if(rightb->balance == LH) {
            node->balance = RH;
            leftb->balance = EH;
        }
        else if(rightb->balance == EH) {
            leftb->balance = EH;
            node->balance = EH;
        }
        else {
            node->balance = EH;
            leftb->balance = LH;
        }
        rightb->balance = EH;
        node->pLeft = rotateLeft(leftb);
        node = rotateRight(node);
    }
    return node;
}

Node* rightBalance(Node *&node)
{
    Node *rightb = node->pRight;
    if(rightb->balance == RH) {
        node = rotateLeft(node);
        node->balance = EH;
        node->pLeft->balance = EH;
    }
    else {
        Node *leftb = rightb->pLeft;
        if(leftb->balance == RH) {
            node->balance = LH;
            rightb->balance = EH;
        }
        else if(leftb->balance == EH) {
            rightb->balance = EH;
            node->balance = EH;
        }
        else {
            node->balance = EH;
            rightb->balance = RH;
        }
        leftb->balance = EH;
        node->pRight = rotateRight(rightb);
        node = rotateLeft(node);
    }
    return node;
}


Node* insertRec(Node *&node, const T &value, bool &taller)
{
    //Node<T> *newprt = new Node<T>(value);
    if(node == NULL) {
        node = new Node(value);
        taller = 1;
        return node;
    }
    if(value < node->data) {
        node->pLeft = insertRec(node->pLeft, value, taller);
        if(taller) {
            if(node->balance == LH) {
                node = leftBalance(node);
                taller = 0;
            }
            else if(node->balance == EH) {
                node->balance = LH;
            }
            else {
                node->balance = EH;
                taller = 0;
            }
        }
    }
    else {
        if (value >= node->data) {
            node->pRight = insertRec(node->pRight, value, taller);
            if(taller) {
                if(node->balance == LH) {
                    node->balance = EH;
                    taller = 0;
                }
                else if(node->balance == EH) {
                    node->balance = RH;
                }
                else {
                    node = rightBalance(node);
                    taller = 0;
                }
            }
        } else {
            taller=0;
            return node;
        }
    }
    return node;
}


void insert(const T &value){
    //TODO
    bool taller = 0;
    this->insertRec(this->root, value, taller);
}



    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};


int main(){
AVLTree<int> avl;
int arr[] = {20,10,40,5,7,42,2,6,15};
for (int i = 0; i < 9; i++){
avl.insert(arr[i]);
}
avl.remove(40);
avl.remove(20);
avl.remove(6);
avl.remove(10);
avl.remove(42);
avl.remove(15);
avl.printTreeStructure();
}