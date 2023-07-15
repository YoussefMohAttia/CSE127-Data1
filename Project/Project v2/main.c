#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
     return 3;
  case '^':
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
  case '^':
     return pow(x,y);
    }
}
char*infixTopostfix(char *infix,char* post)
{
    int i=0;
    char x[2];
    stack*s=initialize();
    post[0]='\0';
    char*token=strtok(infix," ");
    while(token!=NULL)
    {
        if(isdigit(token[0]))
           {
            strcat(post,token);
            strcat(post," ");
           }
        else if(isempty(s))
        {
            push(s,token[0]);
        }
        else if(token[0] == ')')
        {
            while(top(s) != '(')
           {
            x[0]=pop(s);
            x[1]='\0';
            strcat(post,x);
            strcat(post," ");
           }
            pop(s);
        }
        else
        {
        while(!isempty(s) && top(s)!='(' && priority(top(s))>= priority(token[0]))
             {
              x[0]=pop(s);
              x[1]='\0';
              strcat(post,x);
              strcat(post," ");
             }
              push(s,token[0]);
        }
        token=strtok(NULL," ");
    }
       while(!isempty(s))
{
        x[0]=pop(s);
        x[1]='\0';
        strcat(post,x);
        strcat(post," ");
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
    gets(infix);
    infixTopostfix(infix,postfix);
    printf("\n");
    printf("%s\n",postfix);
 //   printf("Result=%.1f",evaluatePostfix(postfix));
    return 0;
}
