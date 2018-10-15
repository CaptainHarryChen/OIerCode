#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=100005;

struct AdjEdge
{
	int v,d;
	AdjEdge(int a,int b)
	{v=a;d=b;}
};

int N;
int fa[MAXN],siz[MAXN],dis[MAXN];
int val[MAXN];
vector<AdjEdge> adj[MAXN];

void dfs(int u)
{
	siz[u]=1;
	for(auto e:adj[u])
	{
		if(e.v==fa[u])
			continue;
		fa[e.v]=u;
		dis[e.v]=e.d;
		dfs(e.v);
		val[u]=max(val[u],siz[e.v]);
		siz[u]+=siz[e.v];
	}
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		int u,v,d;
		scanf("%d%d%d",&u,&v,&d);
		adj[u].emplace_back(v,d);
		adj[v].emplace_back(u,d);
	}
	
	dfs(1);
	int c1=-1,c2=-1,best=0x7F7F7F7F;
	long long ans=0;
	for(int i=1;i<=N;i++)
	{
		if(fa[i])
			ans+=2LL*min(siz[i],siz[1]-siz[i])*dis[i];
		
		int tmp=max(val[i],siz[1]-siz[i]);
		if(tmp==best)
			c2=i;
		if(tmp<best)
			best=tmp,c1=i,c2=-1;
	}
	if(c2!=-1)
	{
		if(fa[c2]==c1)
			ans-=dis[c2];
		else
			ans-=dis[c1];
	}
	else
	{
		int mn=0x7F7F7F7F;
		for(auto e:adj[c1])
			mn=min(mn,e.d);
		ans-=mn;
	}
	printf("%lld\n",ans);
	
	return 0;
}
