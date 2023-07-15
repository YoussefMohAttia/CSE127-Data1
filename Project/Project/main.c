#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("Stack is no");
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
        printf("Stack is empty");
        return;
    }
    else
    return s->head->data;
}
int isempty(stack*s)
{
 return s->head == NULL;
}
void display (stack*s)
{
    node *temp = s->head;
    while (temp != NULL)
    {
        printf("%.1f ",temp->data);
        temp = temp->next;
    }
}
int priority(char x)
{
    switch(x)
    {
  case '(':
     return 2;
  case '*':
  case '/':
     return 1;
  default:
      return 0;
    }
}
float calc(float x,float y,char c)
{
    switch(c)
    {
  case '+':
     return x+y;
  case '-':
     return x-y;
  case '*':
     return x*y;
  case '/':
     return x/y;
    }
}
char*infixTopostfix(char *infix,char* post)
{
    int i=0,k=0;
    stack*s=initialize();
    for(i=0;i<strlen(infix);i++)
    {
        if(isdigit(infix[i]))
           {
            post[k++]=infix[i];
           }
        else if(isempty(s))
        {
            push(s,infix[i]);
        }
        else if(infix[i] == ')')
        {
            while(top(s) != '(')
           {
            post[k++]=pop(s);
           }
            pop(s);
        }
        else
        {
        while(!isempty(s) && top(s)!='(' && priority(top(s))>=priority(infix[i]) )
             {
              post[k++]=pop(s);
             }
              push(s,infix[i]);
        }
    }
       while(!isempty(s))
{
        post[k++]=pop(s);
       post[k]='\0';
}
     return post;
}
float evaluatePostfix(char* post)
{
   stack*s=initialize();
   int i;
   for(i=0;i<strlen(post);i++)
   {
     if(isdigit(post[i]))
        push(s,post[i]-'0');
     else
     {
        float x=pop(s);
        float y=pop(s);
        float z=calc(y,x,post[i]);
        push(s,z);
     }
   }
   return pop(s);
}
int main()
{
    char infix[100],postfix[100];
    printf("Enter the expression :");
    scanf("%s",infix);
    infixTopostfix(infix,postfix);
    printf("\n");
    printf("%s\n",postfix);
    printf("Result=%.1f",evaluatePostfix(postfix));
    return 0;
}
