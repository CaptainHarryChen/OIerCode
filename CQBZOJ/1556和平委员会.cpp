#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=8005*2,MAXM=20005*2;
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
int n,m;
Graph G,g;
int dfn[MAXN],low[MAXN],dfc;
int stack[MAXN],top;
bool ind[MAXN];
int blkid[MAXN],blkc;
vector<int>blk[MAXN];
void tarjan(int u)
{
	dfn[u]=low[u]=++dfc;
	stack[++top]=u;
	ind[u]=true;
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
			blk[blkc].push_back(stack[top]);
			top--;
		}while(stack[top+1]!=u);
	}
}
int in[MAXN],other[MAXN];
void make_g()
{
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
	for(int i=1;i<=n;i++)
	{
		other[blkid[i]]=blkid[((i-1)^1)+1];
		if(blkid[((i-1)^1)+1]==blkid[i])
		{
			printf("NIE\n");
			exit(0);
		}
	}
	for(int i=1;i<=blkc;i++)
		sort(blk[i].begin(),blk[i].end());
	for(int i=1;i<=n;i++)
		for(Edge *p=G.V[i];p;p=p->next)
			if(blkid[p->v]!=blkid[i])
			{
				g.add_edge(blkid[i],blkid[p->v]);
				in[blkid[i]]++;
			}
}
bool cmp(int a,int b)
{
	return blk[a][0]<blk[b][0];
}
int choose[MAXN],pri[MAXN];
int ch[MAXN],tot;
bool chose(int i)
{
	if(choose[i])
		return choose[i]==1;
	choose[i]=1;
	choose[other[i]]=2;
	ch[++tot]=i;
	for(Edge *p=g.V[i];p;p=p->next)
		if(!chose(p->v))
			return false;
	return true;
}
void solve()
{
	for(int i=1;i<=blkc;i++)
		pri[i]=i;
	sort(pri+1,pri+blkc+1,cmp);
	for(int i=1;i<=blkc;i++)
	{
		if(choose[pri[i]])
			continue;
		tot=0;
		if(!chose(pri[i]))
		{
			for(int j=1;j<=tot;j++)
				choose[ch[j]]=choose[other[ch[j]]]=0;
			chose(other[pri[i]]);
		}
	}
}
int ans[MAXN],acnt;
int main()
{
	int a,b;
	scanf("%d%d",&n,&m);
	n*=2;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		G.add_edge(a,((b-1)^1)+1);
		G.add_edge(b,((a-1)^1)+1);
	}
	make_g();
	solve();
	for(int i=1;i<=blkc;i++)
	{
		if(choose[i]!=1)
			continue;
		int sz=blk[i].size();
		for(int j=0;j<sz;j++)
			ans[++acnt]=blk[i][j];
	}
	sort(ans+1,ans+n/2+1);
	for(int i=1;i<=n/2;i++)
		printf("%d\n",ans[i]);
	return 0;
}
