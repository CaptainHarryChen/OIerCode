#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
#define MAXN 100005
int n,m;
int P[MAXN];
int mx[MAXN],mn[MAXN];
bool vis[MAXN];
struct Edge
{
	int t;
	Edge *next,*last;
}edge[MAXN];
void add_edge(int x,int y)
{
	Edge *p=new Edge;
	p->t=y;
	p->next=edge[x].next;
	edge[x].next=p;
	p=new Edge;
	p->t=x;
	p->last=edge[y].last;
	edge[y].last=p;
}
void SPFA1()
{
	memset(vis,0,sizeof vis);
	memset(mn,0x7F,sizeof mn);
	queue<int>Q;
	Q.push(1);
	vis[1]=1;
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();vis[t]=0;
		for(Edge *p=edge[t].next;p;p=p->next)
			if(min(mn[t],P[p->t])<mn[p->t])
			{
				mn[p->t]=min(mn[t],P[p->t]);
				if(!vis[p->t])
				{
					vis[p->t]=1;
					Q.push(p->t);
				}
			}
	}
}
void SPFA2()
{
	memset(vis,0,sizeof vis);
	memset(mx,0,sizeof mx);
	queue<int>Q;
	Q.push(n);
	vis[n]=1;
	while(!Q.empty())
	{
		int t=Q.front();
		Q.pop();vis[t]=0;
		for(Edge *p=edge[t].last;p;p=p->last)
			if(max(mx[t],P[p->t])>mx[p->t])
			{
				mx[p->t]=max(mx[t],P[p->t]);
				if(!vis[p->t])
				{
					vis[p->t]=1;
					Q.push(p->t);
				}
			}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&P[i]);
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y);
		if(z==2)
			add_edge(y,x);
	}
	SPFA1();
	SPFA2();
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,mx[i]-mn[i]);
	printf("%d\n",ans);
	return 0;
}
