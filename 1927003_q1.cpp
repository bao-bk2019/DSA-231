#include<stdio.h>
#include<iostream>
using namespace std;
template <class T>
class SLinkedList {
    public:
        class Node;
    private:
        Node* head;
        Node* tail;
        int count = 0;
    public:
        void    add(const T& data);
        void    add(int index, const T& data);
        void toString(){
            Node* temp = head;
            for (int i = 0; i < count; i++)
            {
                cout<< temp->data << " ";
                temp = temp->next;
            }
            
        }
    public:
        class Node{
            private:
                T data;
                Node* next;
                friend class SLinkedList<T>;
            public:
                Node(const T & data, Node * next = NULL){
                    this->data = data;
                    this->next = next;
                }
        };
};

template <class T>
void SLinkedList<T>::add(const T& data)
{
    if(this->count == 0){
        Node* newNode = new Node(data, nullptr);
        this->head = this->tail = newNode;
    }else{
        Node* newNode = new Node(data, nullptr);
        this->tail->next = newNode;
        this->tail = newNode;
    }
    count++;
}
template <class T>
void SLinkedList<T>::add(int index,const T& data)
{
    /* Insert an element into the list at given index. */ 
    if(index < 0 || index > this->count)
        throw std::out_of_range("Invalid index");
    if(count == 0 || index == count){
        return add(data);
    }
    if(index == 0){
        Node* newNode = new Node(data, nullptr);
        newNode->next = this->head;
        this->head = newNode;
        count++;
        return ;
    }
    Node* tmp = new Node(data, nullptr);
    Node* prev = this->head;
    for(int i=0 ; i < index-1 ; i++ ){
        prev = prev->next;
    }
    tmp->next = prev->next;
    prev->next = tmp;
    count ++;
    
}

int main(){
    SLinkedList<int> list;

    int size = 10;

    for(int index = 0; index < size; index++){
        list.add(0, index);
    }

    list.toString();
}