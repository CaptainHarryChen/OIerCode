#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=200005,INF=0x3F3F3F3F,MAXLOG=20;
const long long LLF=0x3F3F3F3F3F3F3F3FLL;

struct Edge
{
	int u,v,c,w,id;
	Edge(int u=0,int v=0,int c=0,int w=0,int id=0)
	:u(u),v(v),c(c),w(w),id(id){}
	bool operator < (const Edge &t)const
	{return w<t.w;}
};

struct AdjEdge
{
	int v,w,id;
	AdjEdge(int v=0,int w=0,int id=0)
	:v(v),w(w),id(id){}
};

namespace DSU
{
	int fa[MAXN];
	int Root(int x)
	{
		if(fa[x]==0)
			return x;
		return fa[x]=Root(fa[x]);
	}
	bool Union(int x,int y)
	{
		int r1=Root(x),r2=Root(y);
		if(r1==r2)
			return false;
		fa[r1]=r2;
		return true;
	}
}

vector<AdjEdge> adj[MAXN];
void AddEdge(Edge e)
{
	adj[e.u].push_back(AdjEdge(e.v,e.w,e.id));
	adj[e.v].push_back(AdjEdge(e.u,e.w,e.id));
}

int N,M,S;
long long ans,sumw;
int minc,mincid,delid;
Edge E[MAXN];
bool used[MAXN];

void Kruskal()
{
	sort(E+1,E+M+1);
	sumw=0;minc=INF;
	for(int i=1;i<=M;i++)
		if(DSU::Union(E[i].u,E[i].v))
		{
			sumw+=E[i].w;
			if(minc>E[i].c)
			{
				minc=E[i].c;
				mincid=E[i].id;
			}
			used[E[i].id]=true;
			AddEdge(E[i]);
		}
}

namespace LCA
{
	int dep[MAXN],fa[MAXN][MAXLOG];
	pair<int,int> maxw[MAXN][MAXLOG];
	
	void dfs(int u,int f=0,int deep=1)
	{
		dep[u]=deep;
		fa[u][0]=f;
		for(int i=0;i<(int)adj[u].size();i++)
		{
			int v=adj[u][i].v;
			if(v!=f)
			{
				maxw[v][0]=make_pair(adj[u][i].w,adj[u][i].id);
				dfs(v,u,deep+1);
			}
		}
	}
	void InitLCA()
	{
		dfs(1);
		for(int j=1;j<MAXLOG;j++)
			for(int i=1;i<=N;i++)
				if(dep[i]-(1<<j)>0)
				{
					fa[i][j]=fa[fa[i][j-1]][j-1];
					maxw[i][j]=max(maxw[i][j-1],maxw[fa[i][j-1]][j-1]);
				}
	}
	void Query(int u,int v,int &lca,int &mxw,int &mxid)
	{
		if(dep[u]>dep[v])
			swap(u,v);
		pair<int,int> best(0,0);
		for(int j=MAXLOG-1;j>=0;j--)
			if(dep[v]-(1<<j)>=dep[u])
			{
				best=max(best,maxw[v][j]);
				v=fa[v][j];
			}
		if(u==v)
		{
			lca=u;
			mxw=best.first;
			mxid=best.second;
			return;
		}
		for(int j=MAXLOG-1;j>=0;j--)
			if(dep[u]-(1<<j)>0&&fa[u][j]!=fa[v][j])
			{
				best=max(best,max(maxw[u][j],maxw[v][j]));
				u=fa[u][j];
				v=fa[v][j];
			}
		best=max(best,max(maxw[u][0],maxw[v][0]));
		lca=fa[u][0];
		mxw=best.first;
		mxid=best.second;
		return;
	}
}

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
		scanf("%d",&E[i].w);
	for(int i=1;i<=M;i++)
		scanf("%d",&E[i].c);
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d",&E[i].u,&E[i].v);
		E[i].id=i;
	}
	scanf("%d",&S);
	
	Kruskal();
	ans=sumw-S/minc;
	
	LCA::InitLCA();
	
	for(int i=1;i<=M;i++)
		if(!used[E[i].id]&&E[i].c<minc)
		{
			int lca,mxw,id;
			LCA::Query(E[i].u,E[i].v,lca,mxw,id);
			long long tmp=sumw-mxw+E[i].w-S/E[i].c;
			if(ans>tmp)
			{
				ans=tmp;
				mincid=E[i].id;
				delid=id;
			}
		}
	
	printf("%I64d\n",ans);
	for(int i=1;i<=M;i++)
		if((used[E[i].id]&&delid!=E[i].id)||E[i].id==mincid)
		{
			if(mincid==E[i].id)
				E[i].w-=S/E[i].c;
			printf("%d %d\n",E[i].id,E[i].w);
		}
	
	return 0;
}
