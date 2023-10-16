#include<stdio.h>
#include<iostream>
#include<iterator>
#include<sstream>
#include<string>
using namespace std;
template <class T>
class DLinkedList
{
public:
    class Iterator; //forward declaration
    class Node;     //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;
public:
    DLinkedList() : head(NULL), tail(NULL), count(0){};
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &item);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
    void toString(){
        Node *temp = this->head;
        while (temp != this->tail)
        {
            cout << temp->data << ",";
            temp = temp->next;
        }
    }
    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;
        
        Iterator begin()
        {
            return Iterator(this, true);
        }
        Iterator end()
        {
            return Iterator(this, false);
        }

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
    class Iterator
    {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
    };
};


template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) 
{
    this->pList = pList;
    
    if (begin)
    {
        current = pList->head;
        index = 0;
    }
    else
    {
        current = pList->tail;
        index = pList->count - 1;
    }
    
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator)
{
    if (this != &iterator)
        {
            pList = iterator.pList;
            current = iterator.current;
            index = iterator.index;
        }
    return *this;
    
}

template <class T> 
void DLinkedList<T>::Iterator::set(const T &e)
{
    if (current)
        {
            pList->set(index, e);
        }
}

template<class T>
T& DLinkedList<T>::Iterator::operator*() 
{
    if (current)
        {
            return current->data;
        }
    throw std::runtime_error("Dereferencing an invalid iterator");
}

template<class T>
void DLinkedList<T>::Iterator::remove() 
{
    /*
    * TODO: delete Node in pList which Node* current point to. 
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
//    DLinkedList<T>::Node *temp = current->previous;
//    pList->removeAt(index);
//    current = temp;
//    if(current == nullptr){
//     current = pList->head;
//     index = 0;
//    }else index--;
pList->removeAt(index);
index--;
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator) 
{
    return current != iterator.current;
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++() 
{
    if (current)
        {
            current = current->next;
            index++;
        }
    return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int) 
{
    Iterator temp = *this;
        ++(*this);
        return temp;
}



template <class T>
void DLinkedList<T>::add(const T &e)
{   
    if(count == 0){
        this->head = this->tail = new Node(e);
        count++;
        return ;
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
return indexOf(item) != -1;;}
template<class T>
DLinkedList<T>::~DLinkedList(){
    this->clear();
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

int main(){

    DLinkedList<int> list;
int size = 10;
for (int idx = 0; idx < size; idx++)
{
    list.add(idx);
}

DLinkedList<int>::Iterator it = list.begin();
while (it != list.end())
{
    it.remove();
    it;
}
list.toString();
}