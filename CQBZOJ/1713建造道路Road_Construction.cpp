#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005;
struct Edge
{
	int v;
	bool vis;
	Edge *next,*back;
};
struct Graph
{
	Edge *V[MAXN],E[MAXN*2],*cur;
	Graph(){clear();}
	void clear()
	{
		memset(V,0,sizeof V);
		cur=E;
	}
	void add_edge(int a,int b)
	{
		cur->v=b;
		cur->vis=false;
		cur->next=V[a];
		cur->back=cur+1;
		V[a]=cur++;
		cur->v=a;
		cur->vis=false;
		cur->next=V[b];
		cur->back=cur-1;
		V[b]=cur++;
	}
};
Graph G,g;
int stack[MAXN],top;
int dfn[MAXN],dfc,low[MAXN];
int blkcnt,bri[MAXN][2],blkid[MAXN];
void dfs(int u)
{
	dfn[u]=low[u]=++dfc;
	stack[++top]=u;
	for(Edge *p=G.V[u];p;p=p->next)
	{
		if(!dfn[p->v])
		{
			p->vis=true;
			p->back->vis=true;
			dfs(p->v);
			low[u]=min(low[u],low[p->v]);
			if(low[p->v]>dfn[u])
			{
				blkcnt++;
				bri[blkcnt][0]=u;
				bri[blkcnt][1]=p->v;
				while(dfn[stack[top]]>=dfn[p->v])
				{
					blkid[stack[top]]=blkcnt;
					top--;
				}
			}
		}
		else if(!p->vis)
			low[u]=min(low[u],dfn[p->v]);
	}
}
int lcnt;
void search_leaves(int u)
{
	bool flag=true;
	int cnt=0;
	for(Edge *p=g.V[u];p;p=p->next)
	{
		cnt++;
		if(!p->vis)
		{
			flag=false;
			p->vis=true;
			p->back->vis=true;
			search_leaves(p->v);
		}
	}
	lcnt+=(cnt<=1||flag);
}
int main()
{
	int N,M,a,b;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d",&a,&b);
		G.add_edge(a,b);
	}
	dfs(1);
	blkcnt++;
	while(top)
	{
		blkid[stack[top]]=blkcnt;
		top--;
	}
	if(blkcnt==1)
	{
		printf("0\n");
		return 0;
	}
	for(int i=1;i<blkcnt;i++)
		g.add_edge(blkid[bri[i][0]],blkid[bri[i][1]]);
	search_leaves(1);
	printf("%d\n",(lcnt+1)/2);
	return 0;
}
