#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN=105,MAXE=MAXN*MAXN;
struct Edge
{
	int v;
	Edge *next;
};
struct Graph
{
	Edge E[MAXE],*V[MAXN],*cur;
	Graph()
	{clear();}
	void clear()
	{
		memset(V,0,sizeof V);
		cur=E;
	}
	void add_edge(int a,int b)
	{
		cur->v=b;
		cur->next=V[a];
		V[a]=cur++;
	}
};
Graph G;
int dfn[MAXN],low[MAXN],dfc;
bool ind[MAXN];
int stack[MAXN],top;
int blkid[MAXN],blkc;
void tarjan(int u)
{
	dfn[u]=low[u]=++dfc;
	ind[u]=true;
	stack[++top]=u;
	for(Edge *p=G.V[u];p;p=p->next)
	{
		int v=p->v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ind[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		blkc++;
		do
		{
			ind[stack[top]]=false;
			blkid[stack[top]]=blkc;
			top--;
		}while(stack[top+1]!=u);
	}
}
Graph g;
int in[MAXN],out[MAXN];
void make_g(int n)
{
	for(int u=1;u<=n;u++)
		if(!dfn[u])
			tarjan(u);
	for(int u=1;u<=n;u++)
		for(Edge *p=G.V[u];p;p=p->next)
			if(blkid[u]!=blkid[p->v])
			{
				g.add_edge(blkid[u],blkid[p->v]);
				in[blkid[p->v]]++;
				out[blkid[u]]++;
			}
}
int main()
{
	int n,v;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		while(true)
		{
			scanf("%d",&v);
			if(v==0)
				break;
			G.add_edge(i,v);
		}
	make_g(n);
	int cnt1=0,cnt2=0;
	for(int i=1;i<=blkc;i++)
	{
		cnt1+=(in[i]==0);
		cnt2+=(out[i]==0);
	}
	printf("%d\n%d\n",cnt1,blkc==1?0:max(cnt1,cnt2));
	return 0;
}
