#include <iostream>

class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class CircularDoublyLinkedList {
private:
    Node* head;
public:
    CircularDoublyLinkedList() : head(nullptr) {}

    void append(int data) {
        Node* new_node = new Node(data);
        if (!head) {
            head = new_node;
            head->prev = head;
            head->next = head;
        } else {
            Node* last_node = head->prev;
            last_node->next = new_node;
            new_node->prev = last_node;
            new_node->next = head;
            head->prev = new_node;
        }
    }

    void shellSort() {
        int length = 0;
        Node* temp = head;
        do {
            length++;
            temp = temp->next;
        } while (temp != head);

        int gap = length / 2;
        while (gap > 0) {
            Node* current = head;
            for (int i = gap; i < length; ++i) {
                for (int j = i - gap; j >= 0; j -= gap) {
                    Node* prev_node = current->prev;
                    while (prev_node != head && prev_node->data > current->data) {
                        std::swap(prev_node->data, current->data);
                        current = prev_node;
                        prev_node = current->prev;
                    }
                }
                current = current->next;
            }
            gap /= 2;
        }
    }

    void display() {
        if (!head) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        Node* temp = head;
        do {
            std::cout << temp->data << " ";
            temp = temp->next;
        } while (temp != head);
        std::cout << std::endl;
    }

    ~CircularDoublyLinkedList() {
        if (head) {
            Node* current = head;
            Node* next = nullptr;
            do {
                next = current->next;
                delete current;
                current = next;
            } while (current != head);
        }
    }
};

int main() {
    CircularDoublyLinkedList cdll;
    cdll.append(5);
    cdll.append(2);
    cdll.append(9);
    cdll.append(1);
    cdll.append(5);
    cdll.append(6);

    std::cout << "Original list:" << std::endl;
    cdll.display();

    cdll.shellSort();

    std::cout << "\nSorted list:" << std::endl;
    cdll.display();

    return 0;
}
