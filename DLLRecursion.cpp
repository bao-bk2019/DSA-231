#include<stdio.h>
#include<iostream>
#include <cassert>
using namespace std;
class IntDLinkedList
{
private:
    class Node;
private:
    Node *head;
    Node *tail;
    int count;
public:
    IntDLinkedList() : head(NULL), tail(NULL), count(0) {}
    ~IntDLinkedList()
    {
        this->clear();
    }


    void add(int element)
    {
        Node *newNode = new Node(element);
        if (this->head == NULL)
        {
            this->head = newNode;
            this->tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        this->count++;
    }


    void add(int index, int element)
    {
        if (index < 0 || index > count)
        {
           throw std::out_of_range("Index invalid");
        }
        if(this->count == 0){
            this->head = this->tail = new Node(element);
            count++;
            return ;
        }
        this->head = addRecursive(this->head, index, element, 0);
        this->count++;
    }

    Node *addRecursive(Node *current, int index, int element, int currentIndex)
    {
        if (currentIndex == index)
        {
            Node *newNode = new Node(element);
            newNode->next = current;
            if (current->prev != NULL)
            {

                newNode->prev = current->prev;
                current->prev->next = newNode;
            }
            current->prev = newNode;
            return newNode;
        }

        current->next = addRecursive(current->next, index, element, currentIndex + 1);
        return current;
    }

    int removeAt(int index)
    {
        if (index < 0 || index >= this->count)
        {
            // Invalid index
            return -1;
        }

        int removedValue;
        this->head = removeAtRecursive(this->head, index, 0, removedValue);
        this->count--;
        return removedValue;
    }

    Node *removeAtRecursive(Node *current, int index, int currentIndex, int &removedValue)
    {
        if (index == currentIndex)
        {
            removedValue = current->value;
            Node *nextNode = current->next;
            if (current->prev != NULL)
            {
                current->prev->next = current->next;
            }
            if (current->next != NULL)
            {
                current->next->prev = current->prev;
            }
            delete current;
            return nextNode;
        }

        current->next = removeAtRecursive(current->next, index, currentIndex + 1, removedValue);
        return current;
    }

    bool removeItem(int element)
    {
        bool removed = false;
        this->head = removeItemRecursive(this->head, element, removed);
        if (removed)
        {
            this->count--;
        }
        return removed;
    }

    Node *removeItemRecursive(Node *current, int element, bool &removed)
    {
        if (current == NULL)
        {
            return NULL;
        }

        if (current->value == element)
        {
            removed = true;
            Node *nextNode = current->next;
            if (current->prev != NULL)
            {
                current->prev->next = current->next;
            }
            if (current->next != NULL)
            {
                current->next->prev = current->prev;
            }
            delete current;
            return nextNode;
        }

        current->next = removeItemRecursive(current->next, element, removed);
        return current;
    }

    int get(int index)
    {
        if (index < 0 || index >= this->count)
        {
            // Invalid index
            return -1;
        }
        return getRecursive(this->head, index, 0);
    }

    int getRecursive(Node *current, int index, int currentIndex)
    {
        if (currentIndex == index)
        {
            return current->value;
        }
        return getRecursive(current->next, index, currentIndex + 1);
    }

    void set(int index, int element)
    {
        if (index < 0 || index >= this->count)
        {
            // Invalid index
            return;
        }
        setRecursive(this->head, index, 0, element);
    }

    void setRecursive(Node *current, int index, int currentIndex, int element)
    {
        if (currentIndex == index)
        {
            current->value = element;
            return;
        }
        setRecursive(current->next, index, currentIndex + 1, element);
    }

    int indexOf(int element)
    {
        return indexOfRecursive(this->head, element, 0);
    }

    int indexOfRecursive(Node *current, int element, int currentIndex)
    {
        if (current == NULL)
        {
            // Element not found
            return -1;
        }

        if (current->value == element)
        {
            return currentIndex;
        }

        return indexOfRecursive(current->next, element, currentIndex + 1);
    }

    bool contains(int element)
    {
        return indexOf(element) != -1;
    }

    int size()
    {
        return this->count;
    }

    bool empty()
    {
        return this->count == 0;
    }

    void clear()
    {
        clearRecursive(this->head);
        this->head = NULL;
        this->tail = NULL;
        this->count = 0;
    }


    void clearRecursive(Node *current)
    {
        if (current == NULL)
        {
            return;
        }
        clearRecursive(current->next);
        delete current;
    }

    void dump()
    {
        if (this->count == 0)
        {
            assert(this->head == NULL);
            assert(this->tail == NULL);
            cout << "List: []" << endl;
            cout << "Reverse list: []" << endl;
            return;
        }
        
        cout << "List: [";
        Node *temp = this->head;
        while (temp != this->tail)
        {
            cout << temp->value << ",";
            temp = temp->next;
        }
        cout << temp->value << "]" << endl;
        cout << "Reverse list: [";
        temp = this->tail;
        while (temp != this->head)
        {
            cout << temp->value << ",";
            temp = temp->prev;
        }
        cout << temp->value << "]" << endl;
    }
    
private:
    class Node
    {
    public:
        int value;
        Node *prev;
        Node *next;
        Node(int value = 0, Node *prev = NULL, Node *next = NULL) : value(value), prev(prev), next(next) {}
    };
};
int main(){
IntDLinkedList list;
int size = 10;
for (int index = 0; index < size; index++) {
    list.add(list.size(), index);
}

list.dump();
}
