#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 210
using namespace std;
int n,m,cx[MAXN],cy[MAXN];
bool vis[MAXN];
struct cow
{
	int v;
	cow *next;
	cow(){v=0;next=NULL;}
}c[MAXN];
bool bfs(int x)
{
	for(cow*p=c[x].next;p;p=p->next)
	{
		int v=p->v;
		if(vis[v]==0)
		{
			vis[v]=1;
			if(cy[v]==-1||bfs(cy[v]))
			{
				cx[x]=v;
				cy[v]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	int t;
	cin>>n>>m;
	memset(cx,-1,sizeof cx);
	memset(cy,-1,sizeof cy);
	for(int i=1;i<=n;i++)
	{
		c[i].v=i;
		scanf("%d",&t);
		cow*p,*q;
		q=&c[i];
		for(int j=1,x;j<=t;j++)
		{
			scanf("%d",&x);
			p=new cow;
			p->v=x;
			q->next=p;
			q=p;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(cx[i]==-1)
		{
			memset(vis,0,sizeof vis);
			ans+=(int)bfs(i);
		}
	cout<<ans<<endl;
	return 0;
}
	