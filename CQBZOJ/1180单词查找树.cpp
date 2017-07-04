#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int cnt=1;
struct node
{
    char s;
    node* ch[26];
    node(){s=0;memset(ch,0,sizeof ch);}
}*root;
void addnode(string s)
{
    int i;
    node *t;
    for(i=0,t=root;i<s.length();i++)
    {
        if(t->ch[s[i]-'A']==NULL)
        {
            node *tt=new node;
            cnt++;
            t->ch[s[i]-'A']=tt;
            tt->s=s[i];
            t=tt;
        }
        else
            t=t->ch[s[i]-'A'];
    }
}
int main()
{
    string s;
    root=new node;
    for(int i=0;cin>>s;i++)
        addnode(s);
    cout<<cnt<<endl;
    return 0;
}