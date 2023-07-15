#include <stdio.h>
#include <stdlib.h>

typedef struct dnode{

    int data;
    struct dnode* next;
    struct dnode* prev;
}dnode;

typedef struct{
    dnode *head;
    dnode *tail;
}DLL;

DLL* initializeD ()
{
    DLL *l = malloc(sizeof(DLL));
    l->head = l->tail = NULL;

    return l;
}
dnode* newnodeD (int x)
{
    dnode *n = malloc(sizeof(dnode));
    n->data = x;
    n->next = n->prev = NULL;

    return n;
}
void displayD (DLL *l)
{
    dnode* temp = l->head;
    if (l->head == NULL)
        return;
    do
    {
        printf ("%d ", temp ->data);
        temp = temp->next;
    }while (temp != l->head);
    printf("\n");
}
void insertbeginD(DLL *l, int x)
{
    dnode *n = newnodeD(x);
    if (l->head == NULL)
    {
        l->head = l->tail = n;
        l->head->next = l->head;
    }
    else{
        n->next = l->head;
        l->head->prev = n;
        l->head = n;
        l->tail->next = l->head;
        n->prev = l->tail;
        }
}
void insertendD (DLL *l, int x)
{   dnode *n = newnodeD(x);
    if (l->head == NULL)
    {
        l->head = l->tail = n;
        l->head->next = l->head;
    }
    else{
            n->prev = l->tail;
            l->tail->next = n;
            l->tail = n;
            l->tail->next = l->head;
             l->head->prev = l->tail;
    }
}
void deletebeginD (DLL *l)
{
    if (l->head == NULL)
        return;
    else if (l->head->next == l->head)
    {
        free(l->head);
        l->head = l->tail = NULL;
    }
    else{
        l->head = l->head->next;
        free(l->head->prev);
        l->head->prev = l->tail;
        l->tail->next=l->head;
    }
}
void deleteEndD (DLL *l)
{
    if (l->head == NULL)
        return;
    else if (l->head->next == l->head)
    {
        free(l->head);
        l->head = l->tail = NULL;
    }
    else{
        l->tail = l->tail->prev;
        free (l->tail->next);
        l->tail->next = l->head;
        l->head->prev = l->tail;
    }
}
int listsizeD (DLL *l)
{
    int c = 0;
    dnode *temp = l->head;

    do
    {
        c++;
        temp = temp -> next;
    }while (temp != l->head);
    return c;
}
void printListBackward(DLL*l)
{
    dnode* temp = l->tail;
    if (l->head == NULL)
        return;
    do
    {
        printf ("%d ", temp ->data);
        temp = temp->prev;
    }while (temp != l->tail);
    printf("\n");
}
int IsPalindrome (DLL*l)
{
    dnode* temp = l->head;
    dnode* temp2 = l->tail;
    if (l->head == NULL)
        return 1;
    do
    {
        if(temp->data!=temp2->data)
            return 0;
        temp=temp->next;
        temp2=temp2->prev;
    }while (temp != temp2 && temp!=l->tail );
    return 1;
    printf("\n");
}
int checkSumof2Halves(DLL*l)
{
    int s = listsizeD(l),sum=0,sum2=0,i;
    dnode* temp = l->head;
    dnode* temp2 = l->tail;
    if (l->head == NULL)
        return;
    for(i=0;i<s/2;i++)
    {
      sum+=temp->data;
      sum2+=temp2->data;
      temp=temp->next;
      temp2=temp2->prev;
    }
    if(sum==sum2)
    return 1;
    else return 0;
    printf("\n");
}
DLL*Difference(DLL*l, DLL *a)
{
    int c=1;
    DLL *p = initializeD ();
    dnode* temp = l->head;
    dnode* temp2 = a->head;
    dnode* temp3 = p->head;
    do
    {
        do
        {
          if(temp->data==temp2->data )
            c=0;
          temp2=temp2->next;
        }while(temp2!=a->head);
        temp3=p->head;
        do
        { if(temp3==NULL)
            break;
          if(temp->data==temp3->data)
            c=0;
          temp3=temp3->next;
        }while(temp3!=p->head);
        if(c)
        insertendD(p,temp->data);
        temp=temp->next;
         c=1;
    }while (temp!=l->head );
    printf("\n");
    return p;
}
int main ()
{
    DLL *l = initializeD ();
    DLL *a = initializeD ();
        DLL *x = initializeD ();
    DLL *y = initializeD ();
    insertbeginD(l, 3);
    insertendD(l,5);
    insertendD(l, 3);
    insertbeginD(l, 1);
    insertendD(l,2);
    printf("List L : ");
    displayD(l);
    if(IsPalindrome(l))
    printf("Palindrome\n");
    else printf("not Palindrome\n");
    printf("List L printed backward : ");
    printListBackward(l);
    printf("Size of list L = %d\n", listsizeD(l));
    deleteEndD(l);
    insertendD(l,1);
    printf("List L after modification: ");
    displayD(l);
    if(IsPalindrome(l))
    printf("Palindrome\n");
    else printf("not Palindrome\n");

    insertbeginD(a, 4);
    insertendD(a,9);
    insertendD(a, 7);
    insertbeginD(a, 3);
    insertendD(a,2);
            printf("\n");
        printf("List L : ");
        displayD(l);
        if(checkSumof2Halves(l))
        printf("two halves are equal\n\n");
        else printf("two halves are not equal\n\n");
        printf("List A : ");
        displayD(a);
        if(checkSumof2Halves(a))
        printf("two halves are equal\n\n");
        else printf("two halves are not equal\n\n");

  DLL *p= Difference(l,a);
  printf("new list p 'Difference' Elements in L but not in A : ");
       displayD(p);
       printf("\n");
       insertendD(y, 1);
    insertendD(y,3);
    insertendD(y, 7);
    insertendD(y, 9);
    insertendD(x,2);
    insertendD(x, 5);
    insertendD(x, 7);
    insertendD(x,7);
    printf("list Y then X: \n");

    displayD(y);
    displayD(x);
   DLL *f= Difference(y,x);
  printf("new list F 'Difference' Elements in Y but not in X : ");
       displayD(f);

    return 0;
}
