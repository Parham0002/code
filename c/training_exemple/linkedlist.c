#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void initList(link_t *list)
{
    list->head = NULL;
    list->size = 0;
}

void addd(link_t *list, int value)
{
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    newNode->data = value;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
    }
    else
    {

        Node_t *current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
    printf("Added %d to the list.\n", value);
}

void removee(link_t *list)
{
    if (list->head == NULL)
    {
        printf("List is empty. Nothing to remove.\n");
        return;
    }

    if (list->head->next == NULL)
    {

        free(list->head);
        list->head = NULL;
    }
    else
    {

        Node_t *current = list->head;
        while (current->next->next != NULL)
        {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }

    list->size--;
    printf("Removed last element from the list.\n");
}

void printt(link_t *list)
{
    if (list->head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    Node_t *current = list->head;
    printf("List elements: ");
    while (current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
void destroyy(link_t *list)
{
    Node_t *current = list->head;
    while (current != NULL)
    {
        Node_t *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
    printf("The list has been destroyed.\n");
}