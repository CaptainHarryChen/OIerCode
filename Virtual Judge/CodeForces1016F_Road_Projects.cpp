#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=300005;

struct Edge
{
	int v,w;
	Edge(int _v=0,int _w=0){v=_v;w=_w;}
};

int n,m;
vector<Edge> adj[MAXN];
int nxt[MAXN],val[MAXN],siz[MAXN],f[MAXN];
long long dep[MAXN];
bool flag;

void dfs(int u,int fa=0,long long deep=0)
{
	dep[u]=deep;
	siz[u]=1;
	f[u]=fa;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i].v;
		if(v!=fa)
		{
			dfs(v,u,deep+adj[u][i].w);
			siz[u]+=siz[v];
			if(nxt[v]||v==n)
				nxt[u]=v,val[u]=adj[u][i].w;
		}
	}
	if(siz[u]-siz[nxt[u]]>=3)
		flag=true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		adj[u].push_back(Edge(v,w));
		adj[v].push_back(Edge(u,w));
	}
	dfs(1);
	long long mx=-0x7F7F7F7F7F7F7F7FLL;
	if(!flag)
	{
		int u=1;
		long long tmp=-0x7F7F7F7F7F7F7F7FLL;
		while(u)
		{
			long long tmx=-0x7F7F7F7F7F7F7F7FLL;
			for(int i=0;i<(int)adj[u].size();i++)
			{
				int v=adj[u][i].v;
				if(v!=nxt[u]&&v!=f[u])
					tmx=max(tmx,1LL*adj[u][i].w);
			}
			if(tmp>-0x7F7F7F7F7F7F7F7FLL)
				mx=max(mx,tmp+max(tmx,0LL));
			tmp=max(tmp,tmx);
			tmp-=val[u];
			if(f[f[u]])
				mx=max(mx,1LL*(-val[f[f[u]]]-val[f[u]]));
			if(f[u])
				mx=max(mx,1LL*(-val[f[u]]+tmx));
			u=nxt[u];
		}
	}
	while(m--)
	{
		int w;
		scanf("%d",&w);
		if(flag)
			printf("%I64d\n",dep[n]);
		else
			printf("%I64d\n",min(dep[n],dep[n]+mx+w));
	}
	
	return 0;
}
