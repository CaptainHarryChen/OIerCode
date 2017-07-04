#include<cstdio>
#include<iostream>
using namespace std;
int s;
struct dian
{
	int v;
	dian *next;
}a[205];
int main()
{
	int n,m,k;
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		a[i].v=i;
		a[i].next=NULL;
	}
	int x,y;
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		dian *p=new dian;
		p->v=y-1;
		p->next=a[x-1].next;
		a[x-1].next=p;
	}
	cin>>k;
	for(dian*p=&a[k-1];p!=NULL;p=p->next)
		s++;
	cout<<s-1<<endl;
	return 0;
}
