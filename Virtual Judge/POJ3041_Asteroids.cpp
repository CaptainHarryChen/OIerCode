#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXN 1100
using namespace std;
int N,M,cx[MAXN],cy[MAXN];
bool vis[MAXN];
struct asteroid
{
	int id;
	asteroid *next;
	asteroid(){id=0;next=NULL;}
	asteroid(int x){id=x;next=NULL;}
}node[MAXN];
bool dfs(int u)
{
	for(asteroid*p=node[u].next;p;p=p->next)
	{
		int v=p->id;
		if(!vis[v])
		{
			vis[v]=1;
			if(cy[v]==-1||dfs(cy[v]))
			{
				cx[u]=v;
				cy[v]=u;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	memset(node,0,sizeof node);
	memset(cx,-1,sizeof cx);
	memset(cy,-1,sizeof cy);
	scanf("%d%d",&N,&M);
	int a,b;
	asteroid*p;
	for(int i=0;i<M;i++)
	{
		scanf("%d%d",&a,&b);
		node[a].id=a;
		p=new asteroid(b+N);
		p->next=node[a].next;
		node[a].next=p;
	}
	int ans=0;
	for(int i=1;i<=N;i++)
		if(cx[i]==-1)
		{
			memset(vis,0,sizeof vis);
			ans+=dfs(i);
		}
	printf("%d\n",ans);
	return 0;
}