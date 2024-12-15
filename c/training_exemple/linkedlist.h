#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct node
{
    int data;
    struct node *next;
} Node_t;

typedef struct linkedlist
{
    Node_t *head;
    int size;
} link_t;

void initList(link_t *list);

void addd(link_t *list, int value);

void removee(link_t *list);

void printt(link_t *list);

void destroyy(link_t *list);

#endif // LINKEDLIST_H