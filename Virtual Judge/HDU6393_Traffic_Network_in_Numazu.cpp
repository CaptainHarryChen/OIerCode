#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXLOG=18;

class BIT
{
	long long sum[MAXN];
public:
	void Clear()
	{memset(sum,0,sizeof sum);}
	long long Get(int pos)
	{
		long long ret=0;
		while(pos)
		{
			ret+=sum[pos];
			pos-=(pos&(-pos));
		}
		return ret;
	}
	void Add(int pos,long long val)
	{
		while(pos<MAXN)
		{
			sum[pos]+=val;
			pos+=(pos&(-pos));
		}
	}
};
class DSU
{
	int fa[MAXN];
public:
	void Clear()
	{memset(fa,0,sizeof fa);}
	int Root(int u)
	{
		if(fa[u]==0)
			return u;
		return fa[u]=Root(fa[u]);
	}
	bool Union(int u,int v)
	{
		int r1=Root(u),r2=Root(v);
		if(r1==r2)
			return false;
		fa[r1]=r2;
		return true;
	}
};

struct Edge
{
	int v,w;
	Edge(int _v=0,int _w=0)
	{v=_v;w=_w;}
};

int N,Q,A,B,C;
vector<Edge> adj[MAXN];
BIT S;
DSU D;

int edge[MAXN][3];
int st[MAXN],ed[MAXN],dfc;
int fa[MAXN][MAXLOG],dep[MAXN];
void dfs(int u,int f=0,int d=1,int val=0)
{
	fa[u][0]=f;
	dep[u]=d;
	st[u]=++dfc;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i].v;
		if(v!=f)
			dfs(v,u,d+1,adj[u][i].w);
	}
	ed[u]=dfc;
	S.Add(st[u],val);
	S.Add(ed[u]+1,-val);
}
void InitLCA()
{
	for(int j=1;(1<<j)<=N;j++)
		for(int i=1;i<=N;i++)
			if(dep[i]-(1<<j)>0)
				fa[i][j]=fa[fa[i][j-1]][j-1];
}
int LCA(int u,int v)
{
	if(dep[u]>dep[v])
		swap(u,v);
	for(int j=MAXLOG-1;j>=0;j--)
		if(dep[v]-(1<<j)>=dep[u])
			v=fa[v][j];
	if(u==v)
		return u;
	for(int j=MAXLOG-1;j>=0;j--)
		if(dep[u]-(1<<j)>0&&fa[u][j]!=fa[v][j])
			u=fa[u][j],v=fa[v][j];
	return fa[u][0];
}
long long GetDis(int u,int v)
{
	int l=LCA(u,v);
	long long ld=S.Get(st[l]);
	long long ans=S.Get(st[u])+S.Get(st[v])-2LL*ld;
	return ans;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&Q);
		S.Clear();
		D.Clear();
		for(int i=1;i<=N;i++)
			adj[i].clear();
		for(int i=1,u,v,w;i<=N;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			edge[i][0]=u;edge[i][1]=v;edge[i][2]=w;
			if(!D.Union(u,v))
			{
				A=u;B=v;C=w;
				continue;
			}
			adj[u].push_back(Edge(v,w));
			adj[v].push_back(Edge(u,w));
		}
		dfc=0;
		dfs(1);
		InitLCA();
		int op,X,Y;
		while(Q--)
		{
			scanf("%d%d%d",&op,&X,&Y);
			if(op==0)
			{
				if(edge[X][0]==A&&edge[X][1]==B)
					C=Y;
				else
				{
					if(dep[edge[X][0]]>dep[edge[X][1]])
						swap(edge[X][0],edge[X][1]);
					S.Add(st[edge[X][1]],Y-edge[X][2]);
					S.Add(ed[edge[X][1]]+1,edge[X][2]-Y);
					edge[X][2]=Y;
				}
			}
			else
			{
				long long ans1=GetDis(X,Y);
				long long ans2=GetDis(X,A)+C+GetDis(Y,B);
				long long ans3=GetDis(X,B)+C+GetDis(Y,A);
				printf("%I64d\n",min(ans1,min(ans2,ans3)));
			}
		}
	}
	return 0;
}
