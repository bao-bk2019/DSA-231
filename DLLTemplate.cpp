#include<iostream>
#include<stdio.h>
using namespace std;
template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList();
    ~DLinkedList();
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item);
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
    void toString(){
        Node* temp = head;
        for (int i = 0; i < count; i++)
        {
            cout<< temp->data << " ";
            temp = temp->next;
        }
        
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T &data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };

};
int main(){
DLinkedList<int> list;
int size = 10;
int value[] = {2,5,6,3,67,332,43,1,0,9};

for(int idx=0; idx < size; idx++){
  list.add(value[idx]);
}
list.removeAt(0);
list.toString();
}


template <class T>
DLinkedList<T>::DLinkedList()
{
    this->head = this->tail = nullptr;
    this->count = 0;
}

template <class T>
DLinkedList<T>::~DLinkedList()
{
}

template <class T>
void DLinkedList<T>::add(const T &e)
{
    if (count == 0)
    {
   this->head = this->tail = new Node(e);
   count++;
   return;
    }
    Node* temp = new Node(e);
    temp->previous = this->tail;
    this->tail->next = temp;
    this->tail = temp;
    count++;
}

template <class T>
int DLinkedList<T>::size()
{
return this->count;
}

template <class T>
void DLinkedList<T>::add(int index, const T &e)
{
    if (index < 0 || index > count)
        {
            throw std::out_of_range("out of range");
        }
        
        if (index == 0)
        {
            Node *newNode = new Node(e);
            newNode->next = this->head;
            if (count == 0)
            {
                tail = newNode;
            }
            else
            {
                head->previous = newNode;
            }
            head = newNode;
            count++;
        }
        else if (index == count)
        {
            add(e);
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            Node *newNode = new Node(e);
            newNode->next = temp->next;
            newNode->previous = temp->previous;
            temp->next->previous = newNode;
            temp->next = newNode;
            count++;
        }
}
template <class T>
bool DLinkedList<T>::empty()
{
return this->count == 0;
}

template <class T>
T DLinkedList<T>::get(int index)
{
    if (index < 0 || index >= count)
        throw std::out_of_range("out of range");
    Node* temp;
    if (index < count/2){
        temp = this->head;
        for (int i=0 ; i < index; i++){
            temp = temp->next;
        }
    } else {
        temp = this->tail;
        for (int i=0 ; i < count - index - 1; i++){
            temp = temp->previous;
        }

        
    }
    return temp->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T &e)
{
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("out of range");
        }
        
        Node *temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        temp->data = e;    
}

template <class T>
int DLinkedList<T>::indexOf(const T &item)
{
        Node *temp = head;
        int index = 0;
        while (temp != NULL)
        {
            if (temp->data == item)
            {
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;}

template <class T>
bool DLinkedList<T>::contains(const T &item)
{
return indexOf(item) != -1;
}
template <class T>
T DLinkedList<T>::removeAt(int index)
{
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("out of range");
        }
        
        int removedValue;
        if (count == 1)
        {
            removedValue = head->data;
            delete head;
            head = tail = NULL;
        }
        else if (index == 0)
        {
            removedValue = head->data;
            head = head->next;
            delete head->previous;
            head->previous = NULL;
        }
        else if (index == count - 1)
        {
            removedValue = tail->data;
            tail = tail->previous;
            delete tail->next;
            tail->next = NULL;
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            removedValue = temp->data;
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            delete temp;
        }
        count--;
        return removedValue;
}

template <class T>
bool DLinkedList<T>::removeItem(const T &item)
{
        Node *temp = head;
        int index = 0;
        while (temp != NULL)
        {
            if (temp->data == item)
            {
                removeAt(index);
                return true;
            }
            temp = temp->next;
            index++;
        }
        return false;
}

template <class T>
void DLinkedList<T>::clear()
{
    while (!empty())
    {
        removeAt(0);
    }
}
