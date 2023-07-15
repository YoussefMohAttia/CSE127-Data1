#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    float data;
    struct node* next;
} node;
typedef struct
{
    node* head;
} stack;
stack* initialize ()
{
    stack* s = malloc (sizeof(stack));
    s->head = NULL;
    return s;
}
node* newnode (float x)
{
    node* n = malloc(sizeof(node));
    n->data = x;
    n->next = NULL;
    return n;
}
void push (stack *s, float value)
{
    node *n = newnode(value);
    if (s->head == NULL)
        s->head = n;
    else
    {
        n->next = s->head;
        s->head = n;
    }
}
float pop (stack *s)
{
    if (s->head == NULL)
    {
        printf("Stack is Empty\n");
        return;
    }
    else
    {
        node *temp = s->head;
        s->head = s->head->next;
        float x=temp->data;
        free(temp);
        return x;
    }
}
float top(stack *s)
{
    if (s->head == NULL)
    {
        printf("Stack is Empty\n");
        return;
    }
    else
        return s->head->data;
}
int isempty(stack*s)
{
    return s->head == NULL;
}

typedef struct
{
    int *items;
    int front, rear, capacity, noofelements;
} queue;

queue* init(int n)
{
    queue *q = malloc(sizeof(queue));
    q->items = malloc(n * sizeof(int));
    q->front = q->rear = 0;
    q->capacity = n;
    q->noofelements = 0;

    return q;
}
void enqueue (queue *q, int x)
{
    if (!isFull(q))
    {
        q->items[q->rear] = x;
        q->rear = (q->rear+1)% q->capacity;
        q->noofelements++;
    }
}
int dequeue(queue *q)
{
    if (!isEmpty(q))
    {
        int x = q->items[q->front];
        q->front = (q->front+1)% q->capacity;
        q->noofelements--;
        return x;
    }
}
int isEmpty (queue *q)
{
    return q->noofelements == 0;
}

int isFull (queue *q)
{
    return q->noofelements == q->capacity;
}

int getFront(queue *q)
{
    if (!isEmpty(q))
        return q->items[q->front];
    else
    {
        printf("Queue is Empty\n");
        exit(1);
    }
}
int getRear(queue *q)
{
    if (!isEmpty(q))
        return q->items[q->rear-1];
    else
    {
        printf("Queue is Empty\n");
        exit(1);
    }
}
int size(queue *q)
{
    return q->noofelements;
}
void display(queue *q)
{
    queue *temp = init(20);
    while (!isEmpty(q))
    {
        int x = dequeue(q);
        printf("%d ", x);
        enqueue(temp, x);
    }
    while (!isEmpty(temp))
        enqueue(q, dequeue(temp));
    printf("\n");
}
int countEven(queue *q)
{
    queue *temp = init(20);
    int count = 0;
    while (!isEmpty(q))
    {
        int x = dequeue(q);
        if (x % 2 == 0)
            count++;
        enqueue(temp, x);
    }
    while (!isEmpty(temp))
        enqueue(q, dequeue(temp));
    return count;
}
int max(queue *q)
{
    int count=size(q);
    queue*temp=init(count);
    int max=dequeue(q);
    enqueue(temp,max);
    while(!isEmpty(q))
    {
        int x=dequeue(q);
        if(x>max)
            max=x;
        enqueue(temp,x);
    }
    while(!isEmpty(temp))
        enqueue(q,dequeue(temp));
    return max;
}
void swap(queue *q)
{
    int count=size(q);
    queue*temp=init(count);
    int first = dequeue(q);
    int x=first;
    while(!isEmpty(q))
    {
        enqueue(temp,x);
        x=dequeue(q);
    }
    enqueue(q,x);
    dequeue(temp);
    while(!isEmpty(temp))
    {
        enqueue(q,dequeue(temp));
    }
    enqueue(q,first);
}
void insertindx(queue *q,int value,int indx)
{
    if(isEmpty(q))
        return;
    int count=size(q);
    queue*temp=init(count+1);
    for(int i=1 ; i<indx; i++)
        enqueue(temp,dequeue(q));
    enqueue(temp,value);
    while(!isEmpty(q))
        enqueue(temp,dequeue(q));
    while(!isEmpty(temp))
        enqueue(q,dequeue(temp));
}
queue* reverseOdd (queue *q)
{
      if(isEmpty(q))
        return;
    int count=size(q);
    int x;
    queue*temp=init(count);
    queue*tempr=init(count);
    stack*s=initialize();
     while(!isEmpty(q))
     {
      x = dequeue(q);
    enqueue(temp,x);
    push(s,x);
     }
     while(!isempty(s))
      enqueue(tempr,pop(s));
     int y=dequeue(tempr);
     while(!isEmpty(temp))
     {
       x=dequeue(temp);
       if(x%2==0)
         enqueue(q,x);
       else
       {
        while(!isEmpty(tempr)&&y%2==0)
        {
         y=dequeue(tempr);
        }
        enqueue(q,y);
        y=dequeue(tempr);
       }
     }
   return q;
}
queue* reverse(queue *q, int k)
{
  if(isEmpty(q))
        return;
  stack*s=initialize();
      int count=size(q);
    queue*temp=init(count);
    for(int i=0;i<k;i++)
      push(s,dequeue(q));
    while(!isEmpty(q))
        enqueue(temp,dequeue(q));
    while(!isempty(s))
        enqueue(q,pop(s));
    while(!isEmpty(temp))
        enqueue(q,dequeue(temp));
  return q;
}
int main()
{
    queue *q = init(20);
    enqueue(q, 19);
    enqueue(q, 13);
    enqueue(q, 8);
    enqueue(q, 4);
    enqueue(q, 10);
    enqueue(q, 11);
    enqueue(q, 4);
    enqueue(q, 15);
    enqueue(q, 18);
    enqueue(q, 14);
        printf("Queue q: ");
    display(q);
    printf("the max value in Queue is %d\n", max(q));
    printf("the Queue after swapping front and rear: \n");
    swap(q);
    display(q);
    printf("the Queue after insering 17 at 3rd pos : \n");
    insertindx(q,17,3);
    display(q);
    printf("the Queue after reversing odd : \n");
    queue*n=reverseOdd(q);
    display(n);
    printf("the Queue after reversing first 4 elements : \n");
    n=reverse(q,4);
    display(n);
    return 0;
}
