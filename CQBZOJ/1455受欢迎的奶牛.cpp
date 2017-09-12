#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=10005,MAXM=50005;
struct Edge
{
	int v;
	Edge *next;
};
struct Graph
{
	Edge E[MAXM],*V[MAXN],*cur;
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
Graph G,g;
int dfn[MAXN],dfc,low[MAXN];
int stack[MAXN],top;
int blkid[MAXN],blkc;
int cow[MAXN];
bool ind[MAXN];
void dfs(int u,int fa)
{
	dfn[u]=low[u]=++dfc;
	stack[++top]=u;
	ind[u]=true;
	for(Edge *p=G.V[u];p;p=p->next)
	{
		int v=p->v;
		if(!dfn[v])
		{
			dfs(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(ind[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		blkc++;
		int cnt=0;
		while(stack[top+1]!=u)
		{
			ind[stack[top]]=false;
			blkid[stack[top]]=blkc;
			top--;
			cnt++;
		}
		cow[blkc]=cnt;
	}
}
bool flag[MAXN];
int in[MAXN];
int main()
{
	int n,m,a,b;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		G.add_edge(b,a);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i,-1);
	for(int i=1;i<=n;i++)
	{
		if(blkid[i]==0)
		{
			blkid[i]=++blkc;
			cow[blkc]=1;
		}
		for(Edge *p=G.V[i];p;p=p->next)
		{
			if(blkid[p->v]==0)
			{
				blkid[p->v]=++blkc;
				cow[blkc]=1;
			}
			if(blkid[i]!=blkid[p->v])
				in[blkid[p->v]]++;
		}
	}
	int cnt=0,ans;
	for(int i=1;i<=blkc;i++)
		if(in[i]==0)
		{
			cnt++;
			ans=i;
		}
	if(cnt!=1)
		printf("0\n");
	else
		printf("%d\n",cow[ans]);
	return 0;
}
