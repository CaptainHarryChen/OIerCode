#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXLOG=20;

struct Edge
{
	int u,v,w,id;
	Edge(){}
	Edge(int u,int v,int w,int id):u(u),v(v),w(w),id(id){}
	bool operator < (const Edge &t)const
	{return w<t.w;}
};
struct AdjEdge
{
	int v,w;
	AdjEdge();
	AdjEdge(int v,int w):v(v),w(w){};
};

int dsu[MAXN];
int Root(int x)
{
	if(dsu[x]==0)
		return x;
	return dsu[x]=Root(dsu[x]);
}

int n,m;
bool used[MAXN];
long long ans[MAXN];
Edge edge[MAXN];

vector<AdjEdge> adj[MAXN];
void AddEdge(int u,int v,int w)
{
	adj[u].push_back(AdjEdge(v,w));
	adj[v].push_back(AdjEdge(u,w));
}

int dep[MAXN],fa[MAXN][MAXLOG],mx[MAXN][MAXLOG];
void dfs(int u,int f=0,int deep=1)
{
	dep[u]=deep;
	fa[u][0]=f;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i].v;
		if(v==f)
			continue;
		mx[v][0]=adj[u][i].w;
		dfs(v,u,deep+1);
	}
}
int LCAmx(int u,int v)
{
	if(dep[u]>dep[v])
		swap(u,v);
	int ret=0;
	for(int j=MAXLOG-1;j>=0;j--)
		if(dep[v]-(1<<j)>=dep[u])
		{
			ret=max(ret,mx[v][j]);
			v=fa[v][j];
		}
	if(u==v)
		return ret;
	for(int j=MAXLOG-1;j>=0;j--)
		if(dep[u]-(1<<j)>0&&fa[u][j]!=fa[v][j])
		{
			ret=max(ret,max(mx[u][j],mx[v][j]));
			u=fa[u][j];
			v=fa[v][j];
		}
	ret=max(ret,max(mx[u][0],mx[v][0]));
	return ret;
}

int main()
{
	freopen("BreakCircle_data.in","r",stdin);
	//input
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		edge[i]=Edge(u,v,w,i);
	}
	//Kruskal
	long long sum=0;
	sort(edge+1,edge+m+1);
	for(int i=1;i<=m;i++)
	{
		int r1=Root(edge[i].u),r2=Root(edge[i].v);
		if(r1==r2)
			continue;
		dsu[r1]=r2;
		sum+=edge[i].w;
		used[i]=true;
		AddEdge(edge[i].u,edge[i].v,edge[i].w);
	}
	//InitLCA
	dfs(1);
	for(int j=1;j<MAXLOG;j++)
		for(int i=1;i<=n;i++)
			if(fa[i][j-1]!=0&&fa[fa[i][j-1]][j-1]!=0)
			{
				fa[i][j]=fa[fa[i][j-1]][j-1];
				mx[i][j]=max(mx[i][j-1],mx[fa[i][j-1]][j-1]);
			}
	//solve
	for(int i=1;i<=m;i++)
	{
		if(used[i])
			ans[edge[i].id]=sum;
		else
		{
			int delta=edge[i].w-LCAmx(edge[i].u,edge[i].v);
			ans[edge[i].id]=sum+delta;
		}
	}
	//output
	for(int i=1;i<=m;i++)
		printf("%I64d\n",ans[i]);
	
	return 0;
}
