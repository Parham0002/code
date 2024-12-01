#ifndef EX40_H
#define EX40_H

typedef struct node
{
    int data;
    struct node *next;
} node;

typedef struct linklist
{
    node *head;
    int size;
} linklist;

// Function prototypes
linklist *create();
void insert(linklist *list, int data);
void change(linklist *list, int old_data, int new_data);
void deletee(linklist *list, int data);
int search(linklist *list, int data);
int nth(linklist *list, int n);
int size(linklist *list);
void destroy(linklist *list);

#endif
