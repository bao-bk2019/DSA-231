#include<stdio.h>
#include<iostream>
using namespace std;
template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count=0;
public:
    SLinkedList();
    ~SLinkedList();
    void    add(T e);
    void    add(int index, T e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, T e);
    int     indexOf(T item);
    bool    contains(T item);
    void    clear();
    T       removeAt(int index);
    bool    removeItem(T item);
    void toString(){
        Node* temp = head;
        for (int i = 0; i < count; i++)
        {
            cout<< temp->data << " ";
            temp = temp->next;
        }
        
    }
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
    };
};
int main(){
    SLinkedList<int> list;

    int size = 10;

    for(int index = 0; index < size; index++){
        list.add(0, index);
    }

    list.toString();
}

template <class T>
SLinkedList<T>::SLinkedList()
{
}

template <class T>
SLinkedList<T>::~SLinkedList()
{
}

template <class T>
void SLinkedList<T>::add(T e)
{
    if(this->count == 0){
        Node* newNode = new Node(e, nullptr);
        this->head = this->tail = newNode;
    }else{
        Node* newNode = new Node(e, nullptr);
        this->tail->next = newNode;
        this->tail = newNode;
    }
    count++;
}

template <class T>
void SLinkedList<T>::add(int index, T e)
{
    /* Insert an element into the list at given index. */ 
    if(index < 0 || index > this->count)
        throw std::out_of_range(" invalid index");
    if(count == 0 || index == count){
        return add(e);
    }
    if(index == 0){
        Node* newNode = new Node(e, nullptr);
        newNode->next = this->head;
        this->head = newNode;
        count++;
        return ;
    }
    Node* tmp = new Node(e, nullptr);
    Node* prev = this->head;
    for(int i=0 ; i < index-1 ; i++ ){
        prev = prev->next;
    }
    tmp->next = prev->next;
    prev->next = tmp;
    count ++;
    
}

template <class T>
int SLinkedList<T>::size()
{
    return this->count;
}
template <class T>
bool SLinkedList<T>::empty()
{
    if (this->count == 0)
    {
        return true;
    }
    
    return false;
}

template <class T>
T SLinkedList<T>::get(int index)
{
    if (index < 0 || index > (this->count -1))
    {
        throw std::out_of_range(" invalid index");
    }
    Node* temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    
    return temp->data;
}

template <class T>
void SLinkedList<T>::set(int index, T e)
{
    if (index < 0 || index > (this->count -1))
    {
        throw std::out_of_range(" invalid index");
    }
    Node* temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    temp->data = e;
    return ;
}

template <class T>
int SLinkedList<T>::indexOf(T item)
{
    Node* temp = this->head;
    for (int i = 0; i < this->count; i++)
    {   if (temp->data == item)
        {
            return i;
        }
    
        temp = temp->next;
    }
    return -1;
}

template <class T>
bool SLinkedList<T>::contains(T item)
{
    Node* temp = this->head;
    for (int i = 0; i < this->count; i++)
    {   if (temp->data == item)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
template <class T>
void SLinkedList<T>::clear()
{
    Node  *iter=this->head, *temp;
    while(iter!=NULL){
        temp=iter;
        iter=iter->next;
        delete temp;
        count--;
    }
    this->tail=NULL;
    this->head=NULL;
    return ;
}
template <class T>
T SLinkedList<T>::removeAt(int index)
{
    if (index < 0 || index >= this->count)
        throw std::out_of_range("out of range");
    if ( count == 1) {
        Node* tmp = this->head;
        this->head =  this->tail = NULL;
        T value = tmp->data;
        delete tmp;
        count--;
        return value;
    }
    if (index == 0){
        Node* tmp = head;
        T value = tmp->data;
        head = head->next;
        delete tmp;
        count--;
        return value;
    }
    Node* prev = head;
    for(int i=0 ; i < index-1 ; i++ ){
        prev = prev->next;
    }
    Node* tmp = prev->next;
    T value = tmp->data;
    prev->next = tmp->next;
    if( index == count-1) this->tail = prev;
    delete tmp;
    count--;
    return value;
}
template <class T>
bool SLinkedList<T>::removeItem(T item)
{
    int x=indexOf(item);
    if(x!=-1){
        removeAt(x);
        return true;
    }

    return false;
}


