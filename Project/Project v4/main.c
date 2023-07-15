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
void display (stack*s)
{
    node *temp = s->head;
    while (temp != NULL)
    {
        printf("%.2f ",temp->data);
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
char*infixTopostfix(char *infix)
{
    int i=0;
    char x[2];
    stack*s=initialize();
    char*post = malloc(sizeof(char)*100);
    post[0]='\0';
    char*token=strtok(infix," ");
    while(token!=NULL)
    {
        if(isdigit(token[0]) || isdigit(token[1]))
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
    char*token=strtok(post," ");
    int i,j,c=0;
    float f,n=-1;
    while(token!=NULL)
    {
        if(!isdigit(token[0])&& isdigit(token[1]))
        {
            c=0;
            f=0;
            i=1;
            while(token[i]!='.' && token[i]!='\0')
            {
                i++;
                c++;
            }
            for(i=1; i<strlen(token); i++)
            {
                if(token[i]=='.')
                {
                    j=1;
                    i++;
                    while(token[i]!='\0')
                    {
                        f+=(token[i]-'0')*pow(0.1,j);
                        j++;
                        i++;
                    }
                }
                else
                f+=(token[i]-'0')*pow(10,c-i);
            }
            f*=n;
            push(s,f);
        }
        else if(isdigit(token[0]) || isdigit(token[1]))
        {
            c=0;
            f=0;
            i=0;
            while(token[i]!='.' && token[i]!='\0')
            {
                i++;
                c++;
            }
            for(i=0; i<strlen(token); i++)
            {
                if(token[i]=='.')
                {
                    j=1;
                    i++;
                    while(token[i]!='\0')
                    {
                        f+=(token[i]-'0')*pow(0.1,j);
                        j++;
                        i++;
                    }
                }
                else
                f+=(token[i]-'0')*pow(10,c-i-1);
            }
            push(s,f);
        }
        else
        {
            float x=pop(s);
            float y=pop(s);
            float z=calc(y,x,token[0]);
            push(s,z);
        }
        token=strtok(NULL," ");
    }
    return pop(s);
}
int main()
{
    char infix[100];
    printf("Enter the expression (with spaces) :");
    gets(infix);
    char*post=infixTopostfix(infix);
    printf("\n");
    printf("%s\n",post);
    printf("%f",evaluatePostfix(post));

    return 0;
}
