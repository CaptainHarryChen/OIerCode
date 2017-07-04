#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int n,m,dfn[5005],low[5005],dfscnt,cutdot,cutside,rs;
struct node
{
	int v;
	node *next;
	node(){v=-1;next=NULL;}
}arr[5005],*p;
void dfs(int u,int fa)
{
	dfn[u]=low[u]=++dfscnt;
	bool f=0;
	for(node *p=&arr[u];p;p=p->next)
	{
		int v=p->v;
		if(!dfn[v])
		{
			if(fa==-1)rs++;
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				if(fa!=-1)
				{
					if(!f)
					{
						cutdot++;
						f=1;
					}
				}
			}
			if(low[v]>dfn[u])
				cutside++;
		}
		else if(v!=fa)
			low[u]=min(low[u],dfn[v]);
	}
}
int main()
{
	int a,b;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&a,&b);
		arr[a].v=a;
		arr[b].v=b;
		p=&arr[a];
		while(p->next!=NULL)p=p->next;
		node *q=new node;
		q->v=b;
		q->next=NULL;
		p->next=q;
		p=&arr[b];
		while(p->next!=NULL)p=p->next;
		q=new node;
		q->v=a;
		q->next=NULL;
		p->next=q;
	}
	dfs(1,-1);
	if(rs>1)
		cutdot++;
	printf("%d\n%d\n",cutdot,cutside);
	return 0;
}
