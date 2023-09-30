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
        if(count == 0){
            this->head = this->tail = new Node(element);
            count++;
            return ;
        }
        Node* temp = new Node(element);
        temp->prev = this->tail;
        this->tail->next = temp;
        this->tail = temp;
        count++;
    }

    void add(int index, int element)
    {
        if (index < 0 || index > count)
        {
            throw std::out_of_range("out of range");
        }
        
        if (index == 0)
        {
            Node *newNode = new Node(element, NULL, head);
            if (count == 0)
            {
                tail = newNode;
            }
            else
            {
                head->prev = newNode;
            }
            head = newNode;
        }
        else if (index == count)
        {
            add(element);
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            Node *newNode = new Node(element, temp, temp->next);
            temp->next->prev = newNode;
            temp->next = newNode;
        }
        count++;
    }

    int removeAt(int index)
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("out of range");
        }
        
        int removedValue;
        if (count == 1)
        {
            removedValue = head->value;
            delete head;
            head = tail = NULL;
        }
        else if (index == 0)
        {
            removedValue = head->value;
            head = head->next;
            delete head->prev;
            head->prev = NULL;
        }
        else if (index == count - 1)
        {
            removedValue = tail->value;
            tail = tail->prev;
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
            removedValue = temp->value;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
        }
        count--;
        return removedValue;
    }

    bool removeItem(int element)
    {
        Node *temp = head;
        int index = 0;
        while (temp != NULL)
        {
            if (temp->value == element)
            {
                removeAt(index);
                return true;
            }
            temp = temp->next;
            index++;
        }
        return false;
    }

    int get(int index)
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
                temp = temp->prev;
            }
        }
        return temp->value;
    }

    void set(int index, int element)
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
        temp->value = element;    
    }

    int indexOf(int element)
    {
        Node *temp = head;
        int index = 0;
        while (temp != NULL)
        {
            if (temp->value == element)
            {
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }

    bool contains(int element)
    {
        return indexOf(element) != -1;;
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
        while (!empty())
            {
                removeAt(0);
            }
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
for(int index = 0; index < size; index++){
    list.add(index);
}

list.dump();
}
