#include <stdio.h>
#include <stdlib.h>
#include "ex40.h"

// Create a new linked list
linklist *create()
{
    linklist *list = (linklist *)malloc(sizeof(linklist));
    list->head = NULL;
    list->size = 0;
    return list;
}

// Insert a node in sorted order
void insert(linklist *list, int data)
{
    if (!list)
        return;

    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;

    if (!list->head || data < list->head->data)
    {
        new_node->next = list->head;
        list->head = new_node;
    }
    else
    {
        node *current = list->head;
        while (current->next && current->next->data < data)
        {
            current = current->next;
        }
        if (current->data == data)
        {
            free(new_node); // Prevent duplicate insertion
            return;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    list->size++;
}

// Change a node's value
void change(linklist *list, int old_data, int new_data)
{
    if (!list)
        return;
    deletee(list, old_data);
    insert(list, new_data);
}

// Delete a node by value
void deletee(linklist *list, int data)
{
    if (!list || !list->head)
        return;

    node *current = list->head;
    node *prev = NULL;

    if (current->data == data)
    {
        list->head = current->next;
        free(current);
        list->size--;
        return;
    }

    while (current && current->data != data)
    {
        prev = current;
        current = current->next;
    }

    if (current)
    {
        prev->next = current->next;
        free(current);
        list->size--;
    }
}

// Search for a node's value
int search(linklist *list, int data)
{
    if (!list)
        return 0;

    node *current = list->head;
    while (current)
    {
        if (current->data == data)
            return 1;
        current = current->next;
    }
    return 0;
}

// Get the nth node's value
int nth(linklist *list, int n)
{
    if (!list || n < 0 || n >= list->size)
        return -1;

    node *current = list->head;
    for (int i = 0; i < n; i++)
    {
        current = current->next;
    }
    return current->data;
}

// Get the size of the list
int size(linklist *list)
{
    return list ? list->size : 0;
}

// Destroy the linked list
void destroy(linklist *list)
{
    if (!list)
        return;

    node *current = list->head;
    while (current)
    {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
