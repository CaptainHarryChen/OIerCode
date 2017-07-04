#include<iostream>
#include<cstring>
using namespace std;
char s1[30],s2[30];
int len;
struct node
{;
    char c;
    node *left,*right;
    node(){c=0;left=right=NULL;}
    node(char x){c=x;left=right=NULL;}
}*root;
void make_tree(node **u,int l,int r,int t)
{
    int x;
    for(x=0;x<r&&s1[x]!=s2[t];x++);
    if(x==r)return;
    *u=new node(s2[t]);
    make_tree(&(*u)->left,l,x,t+1);
    make_tree(&(*u)->right,x+1,r,t+x-l+1);
}
void print_tree(node *u)
{
    if(u==NULL)return;
    print_tree(u->left);
    print_tree(u->right);
    cout<<u->c;
}
int main()
{
    cin>>s2>>s1;
    len=strlen(s1);
    make_tree(&root,0,len,0);
    print_tree(root);
    cout<<endl;
    return 0;
}