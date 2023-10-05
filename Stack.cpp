#ifndef STACK_H
#define STACK_H
template<class T>
class Stack {
protected:
    DLinkedList<T> list;
public:
    Stack() {}
    void push(T item) ;
    T pop() ;
    T top() ;
    bool empty() ;
    int size() ;
    void clear() ;
};
#endif

template <class T>
void Stack<T>::push(T item)
{
    list.add(0);
}

template <class T>
T Stack<T>::pop()
{
    return list.removeAt(0);
}

template <class T>
T Stack<T>::top()
{
    return list.get(0);
}

template <class T>
bool Stack<T>::empty()
{
    return list.empty();
}

template <class T>
int Stack<T>::size()
{
    return list.size();
}

template <class T>
void Stack<T>::clear()
{
    list.clear;
}
template <class T>
class DLinkedList 
{
public:
    class Node;     //forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() ;
    ~DLinkedList();
    void add(const T& e);
    void add(int index, const T& e);
    T removeAt(int index);
    bool removeItem(const T& removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T& e);
    int indexOf(const T& item);
    bool contains(const T& item);
};
