#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    char* data;
    struct node* left;
    struct node* right;
} node;

node* newnode(char* x)
{
    node* n = malloc(sizeof(node));
    n->data=malloc(strlen(x)+1);
    strcpy(n->data, x);
    n->left = n->right = NULL;
    return n;
}

node* insert(node* root, char* x)
{
    if (root == NULL)
    {
        node* n = newnode(x);
        root = n;
    }
    else if (strcasecmp(x, root->data) < 0)
    {
        root->left = insert(root->left, x);
    }
    else
    {
        root->right = insert(root->right, x);
    }

    return root;
}

node* search(node* root, char* x)
{
    if (root == NULL)
        return NULL;
    else if (strcasecmp(root->data, x) == 0)
        return root;
    else if (strcasecmp(x, root->data) < 0)
        return search(root->left, x);
    else
        return search(root->right, x);
}

int count(node*root)
{
    if(root==NULL)
        return 0;
    else return 1+ count(root->left)+count(root->right) ;
}

int Height(node*root)
{
    if (root == NULL)
        return -1;
    int l = Height(root->left);
    int r = Height(root->right);
    if (l > r)
        return l+1;
    else
        return r+1;
}

node*lastnode(node*root,char*x)
{
    if(root==NULL)
        return NULL;
    else if(strcasecmp(x,root->data)<0)
    {
        if(root->left==NULL)
            return root;
        else
            return lastnode(root->left,x);
    }
    else
    {
        if(root->right==NULL)
            return root;
        else
            return lastnode(root->right,x);
    }
}

node* findsuc( node* root,node* n )
{
    if (n->right != NULL)
    {
        node*current = n->right;
        while (current->left != NULL)
            current = current->left;
        return current;
    }
    node* succ = NULL;
    while (root != NULL)
    {
        if (strcasecmp(n->data,root->data)<0)
        {
            succ = root;
            root = root->left;
        }
        else if (strcasecmp(n->data,root->data)>0)
            root = root->right;
        else
            break;
    }
    return succ;
}

node* findpre( node* root,node* n )
{
    if (n->left != NULL)
    {
        node*current = n->left;
        while (current->right != NULL)
            current = current->right;
        return current;
    }
    node* pre = NULL;
    while (root != NULL)
    {
        if (strcasecmp(n->data,root->data)<0)
            root = root->left;
        else if (strcasecmp(n->data,root->data)>0)
            {
            pre = root;
            root = root->right;
            }
        else
            break;
    }
    return pre;
}

int main()
{
    node*root=NULL;
    FILE*f=fopen("EN-US-Dictionary.txt","r");
    char x[30];
    while(!feof(f))
    {
        fscanf(f,"%s",x);
        root=insert(root,x);
    }
    printf("Dictionary Loaded Successfully...!\n");
    printf("..............................\n");
    printf("Size = %d\n",count(root));
    printf("..............................\n");
    printf("Height = %d\n",Height(root));
    printf("..............................\n");
    char sentence[100];
    printf("Enter a Sentence : \n");
    gets(sentence);
    char*p=strtok(sentence," ");
    while(p!=NULL)
    {
        node*m=search(root,p);
        if(m!=NULL)
            printf("%s - CORRECT!\n",p);
        else
        {
            node*k=lastnode(root,p);
            node*s=findsuc(root,lastnode(root,p));
            node*d=findpre(root,lastnode(root,p));
            printf("%s - INCORRECT! ,  ",p);
            printf("Suggestions : %s %s %s\n",k->data,s->data,d->data);
        }
        p=strtok(NULL," ");
    }
    return 0;
}
