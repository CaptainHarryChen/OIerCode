#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;
int n,m,s;
struct dian
{
	int v,rd;
	dian*next;
	dian()
	{next=NULL;rd=0;}
}a[205];
queue<dian>q;
bool f[205];
int b[205],c;
int main()
{
	cin>>n>>m;
	int x,y;
	for(int i=0;i<n;i++)
	{a[i].v=i+1;a[i].next=NULL;}
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		dian*p=new dian;
		p->v=y;
		p->next=a[x-1].next;
		a[x-1].next=p;
		a[y-1].rd++;
	}
	bool ff=0;
	for(int i=0;i<n;i++)
		if(a[i].rd==0)
		{q.push(a[i]);f[i]=1;ff=1;}
	if(!ff)
	{printf("no solution\n");return 0;}
	while(!q.empty())
	{
		dian t=q.front();
		s++;
		b[c++]=t.v;
		q.pop();
		for(dian*p=t.next;p!=NULL;p=p->next)
			a[p->v-1].rd--;
		for(int i=0;i<n;i++)
			if(a[i].rd==0&&f[i]==0)
			{q.push(a[i]);f[i]=1;}
	}
	ff=0;
	for(int i=0;i<n;i++)
		if(a[i].rd==0)
		{q.push(a[i]);f[i]=1;ff=1;}
	if(!ff||s!=n)
	{printf("no solution\n");return 0;}
	for(int i=0;i<c-1;i++)
		printf("%d ",b[i]);
	printf("%d\n",b[c-1]);
	return 0;
}
