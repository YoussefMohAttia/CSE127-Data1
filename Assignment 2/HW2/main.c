#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
} node;
typedef struct
{
    node* head;
    node* tail;
} linkedlist;
linkedlist* initialize ()
{
    linkedlist *l = malloc (sizeof(linkedlist));
    l->head = l->tail = NULL;

    return l;
}
node* newnode (int x)
{
    node* n = malloc(sizeof(node));
    n->data = x;
    n->next = NULL;
    return n;
}
void insertbegin ( linkedlist *l, int x)
{
    node *n = newnode(x);
    if (l->head == NULL)
        l->head = l->tail = n;
    else
    {
        n->next = l->head;
        l->head = n;
    }
}
void display (linkedlist *l)
{
    node *temp = l->head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void insertend (linkedlist *l, int x)
{
    node *n = newnode(x);
    if (l->head == NULL)
        l->head = l->tail = n;
    else
    {
        l->tail->next = n;
        l->tail = n;
    }
}
void deletebegin ( linkedlist *l)
{
    if (l->head == NULL)
        return;
    else
    {
        node *temp = l->head;
        l->head = l->head->next;
        free(temp);
        if(l->head == NULL)
            l->tail = NULL;
    }
}
void deleteEnd (linkedlist *l)
{
    if (l->head == NULL)
        return;
    else if (l->head->next == NULL)
    {
        free(l->head);
        l->head = l->tail = NULL;
    }
    else
    {
        node *prev = l->head;
        while (prev->next != l->tail)
            prev = prev->next;
        free(l->tail);
        l->tail = prev;
        l->tail->next = NULL;
    }
}
int listSize(linkedlist *l)
{
    int c = 0;
    node *temp = l->head;
    while (temp != NULL)
    {
        c++;
        temp= temp->next;
    }
    return c;
}
void insertSorted (linkedlist *l, int x)
{
    node *n = newnode(x);
    node *temp = l->head;
    if (l->head == NULL)
        l->head = l->tail = n;
    else if (temp->data < x)
    {
            while (temp->next->data < x)
    {
        temp = temp->next;
    }
    n->next=temp->next;
    temp->next=n;
    }
     else
    {
            while (temp->next->data > x)
    {
        temp = temp->next;
    }
    n->next=temp->next;
    temp->next=n;
    }
}
int IsEqual (linkedlist *l, linkedlist *p)
{
    node *temp = l->head;
    node *temp2 = p->head;
     while (temp != NULL && temp2 != NULL)
    {
        if (temp->data != temp2->data)
        {
            return 0;
        }
        else
        {
            temp = temp->next;
            temp2 = temp2->next;
        }
    }
    if (temp != NULL || temp2 != NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
void reverseList(linkedlist *l)
{
     node* prev = NULL;
     node* current = l->head;
     node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    l->head= prev;
}
int main()
{
    linkedlist *l = initialize();
    linkedlist *a = initialize();
    linkedlist *p = initialize();
    insertbegin(l, 2);
    insertbegin (l,1);
    insertend (l,3);
    insertend (l,5);
    insertend (l,6);
    printf("sorted list L : ");
    display(l);
    insertSorted(l,4);
    printf("list L after inserting '4' in ascending : ");
    display(l);
    printf("\n");
     insertbegin(a, 5);
     insertbegin (a,6);
     insertend (a,3);
     insertend (a,2);
     printf("sorted list A : ");
     display(a);
     insertSorted(a,4);
     printf("list A after inserting '4' in descending : ");
     display(a);
     printf("\n");

    insertbegin(p, 2);
    insertbegin (p,1);
    insertend (p,3);
    insertend (p,5);
    insertend (p,6);
    insertSorted(p,4);
    printf("New list p : ");
    display(p);

        if(IsEqual(l,p))
        printf("\nList L and P are identical\n");
        else  printf("List L and P not identical\n");

     if(IsEqual(l,a))
        printf("List L and A are identical\n");
        else  printf("List L and A not identical\n\n");

     printf("list L after Reversing : ");
     reverseList(l);
     display(l);
    return 0;
}
