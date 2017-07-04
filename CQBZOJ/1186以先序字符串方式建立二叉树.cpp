#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
using namespace std;
struct node
{
	char v;
	node*l,*r;
	node(){v=0;l=r=NULL;}
};
void xiandfs(node*p)
{
	char c;
	scanf("%c",&c);
	if(c==' ')
		return;
	p->v=c;
	node*s=new node;
	p->l=s;
	xiandfs(s);
	s=new node;
	p->r=s;
	xiandfs(s);
}
void houdfs(node*p)
{
	if(p==NULL||p->v==' '||p->v==0)
		return;
	houdfs(p->l);
	houdfs(p->r);
	printf("%c",p->v);
}
int main()
{
	node*s=new node;
	xiandfs(s);
	houdfs(s);
	printf("\n");
	return 0;
}
