/*
Develop and test a multiple-instance linked list module to strore and restore data of type int according the following requirements.
The data stored in a linked list shall be unique and sorted.
The module shall provide the following functions:
A create function to create an instance of the list.
An insert function to insert an integer in a list.
An available function to return the number of data elements stored in a list.
A search function to check if an integer exists in a list or not
A remove function to delete an integer from a list
An edit function to change the data stored in a node of a list.
Note that the data stored in a list shall always be unique and sorted.
A destroy function to release memory allocated for a list.
Test the module using assertions.
 */
#include <iostream>
#include <cassert>
using namespace std;

// Node structure for the linked list
struct Node
{
    int data;
    Node *next;

    Node(int val) : data(val), next(nullptr) {}
};

// Linked List class
class LinkedList
{
private:
    Node *head; // Pointer to the first node

public:
    // Constructor: Initialize an empty list
    LinkedList() : head(nullptr) {}

    // Destructor: Destroy the list
    ~LinkedList()
    {
        destroy();
    }

    // Create: Clear the list (already done by constructor)
    void create()
    {
        destroy();
        head = nullptr;
    }

    // Insert: Add an element while keeping the list sorted and unique
    void insert(int value)
    {
        if (search(value))
        {
            cout << "Value already exists. Skipping insertion.\n";
            return;
        }

        Node *newNode = new Node(value);

        // Insert at the beginning or in the correct sorted position
        if (!head || value < head->data)
        {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node *current = head;
        while (current->next && current->next->data < value)
        {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Available: Count the number of elements in the list
    int available() const
    {
        int count = 0;
        Node *current = head;
        while (current)
        {
            ++count;
            current = current->next;
        }
        return count;
    }

    // Search: Check if a value exists in the list
    bool search(int value) const
    {
        Node *current = head;
        while (current)
        {
            if (current->data == value)
                return true;
            current = current->next;
        }
        return false;
    }

    // Remove: Delete a specific value from the list
    void remove(int value)
    {
        if (!head)
            return;

        // Handle deletion at the head
        if (head->data == value)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node *current = head;
        while (current->next && current->next->data != value)
        {
            current = current->next;
        }

        if (current->next)
        {
            Node *temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    // Edit: Change the value of a node (while maintaining sorted order)
    void edit(int oldValue, int newValue)
    {
        if (!search(oldValue))
        {
            cout << "Value to edit not found.\n";
            return;
        }

        remove(oldValue);
        insert(newValue);
    }

    // Destroy: Release all allocated memory
    void destroy()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Display: Print the list (for debugging purposes)
    void display() const
    {
        Node *current = head;
        while (current)
        {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr\n";
    }
};

// Test the LinkedList class
void testLinkedList()
{
    LinkedList list;

    // Test insertion
    list.insert(10);
    list.insert(5);
    list.insert(20);
    list.insert(10);               // Duplicate, should not be added
    assert(list.available() == 3); // [5, 10, 20]

    // Test search
    assert(list.search(10) == true);
    assert(list.search(15) == false);

    // Test removal
    list.remove(10);
    assert(list.search(10) == false);
    assert(list.available() == 2); // [5, 20]

    // Test edit
    list.edit(20, 15); // Replace 20 with 15
    assert(list.search(20) == false);
    assert(list.search(15) == true);
    assert(list.available() == 2); // [5, 15]

    // Test destroy
    list.destroy();
    assert(list.available() == 0); // Empty list

    cout << "All tests passed!" << endl;
}

int main()
{
    testLinkedList();
    return 0;
}
