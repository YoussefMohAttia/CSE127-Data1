#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *items;
    int capacity;
    int no_of_elements;
} List;

List* initialize (int N)
{
    List *l = malloc(sizeof(List));
    l->items = malloc(N * sizeof(int));
    l->capacity = N;
    l->no_of_elements = 0;

    return l;
}
int isEmpty(List *l)
{
    return l->no_of_elements==0;
}
int isFull (List *l)
{
    return l->capacity == l->no_of_elements;
}
int size (List *l)
{
    return l->no_of_elements;
}
void insertatEnd (List *l, int value)
{
    if(!isFull(l))
    {
        l->items[l->no_of_elements] = value;
        l->no_of_elements++;
    }
}
void insertatBeginning(List *l, int value)
{
    int i;
    if (!isFull(l))
    {
        for (i = size(l); i>0; i--)
            l->items[i] = l->items[i-1];
        l->items[0] = value;
        l->no_of_elements++;
    }
}
void insertinIndex(List *l, int index, int value)
{
    int i;
    if(!isFull(l))
    {
        if (index > size(l))
            printf("Invalid index");
        else
        {
            for (i = size(l); i>index; i--)
                l->items[i] = l->items[i-1];
            l->items[index] = value;
            l->no_of_elements++;
        }
    }
}
int deleteEnd (List *l)
{
    if (!isEmpty(l))
    {
        l->no_of_elements--;
        return (l->items[l->no_of_elements]);
    }
    else
    {

        printf("List is Empty");
        exit(1);
    }
}
int deleteBeginning (List *l)
{
    int i, x;
    if (!isEmpty(l))
    {
        x = l->items[0];
        for (i = 0; i<size(l); i++)
            l->items[i] = l->items[i+1];

        l->no_of_elements--;
        return x;
    }
    else
    {

        printf("List is Empty");
        exit(1);
    }
}
void displayList (List *l)
{
    int i;
    for (i=0; i<size(l); i++)
        printf("%d ", l->items[i]);
    printf("\n");
}
int GetElement(List *l, int pos)
{
    return l->items[pos];
}
int Occurrence(List *l, int key)
{
    int i,count=0;
    for(i=0; i<size(l); i++)
    {
        if(key == l->items[i])
            count++;
    }
    return count;
}
void SortList(List *l)
{
    int i,j,n=l->no_of_elements,temp;
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(l->items[i]>l->items[j])
            {
                temp=l->items[i];
                l->items[i]=l->items[j];
                l->items[j]=temp;
            }
        }
    }
}
List* Split(List *l, int pos)
{
    int i;
    List *n = initialize(100);
    for(i=size(l)-1;i>=pos;i--)
    {
     insertatBeginning(n,l->items[i]);
     l->no_of_elements--;
    }
    return n;
}
int main()
{
    List *l = initialize(100);
    insertatBeginning(l, 3);
    insertatEnd(l, 1);
    insertatEnd(l, -2);
    insertatBeginning(l, 0);
    insertinIndex(l, 1, 5);
    insertatBeginning(l, 3);
    printf("List L: ");
    displayList(l);
       printf("\nthe Element at index [2]: %d\n",GetElement(l,2));
       printf("the Element at index [4]: %d\n\n",GetElement(l,4));
       printf("Number of Occurrence of Element '3': %d\n",Occurrence(l,3));
       printf("Number of Occurrence of Element '0': %d\n\n",Occurrence(l,0));
       SortList(l);
       printf("List L after sorting: ");
       displayList(l);
       List *n = Split(l,2);
       printf("\nList L after Splitting at index[2] : ");
       displayList(l);
       printf("\nNew List N 'Splitted' : ");
       displayList(n);
    return (0);
}
