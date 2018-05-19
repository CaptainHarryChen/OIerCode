#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=20005;

int n,m;
vector<int> adj[MAXN];

int dfn[MAXN],low[MAXN],dfc,scc;
int stk[MAXN],tot;
bool ind[MAXN];
bool tarjan(int u)
{
	ind[u]=true;
	low[u]=dfn[u]=++dfc;
	stk[++tot]=u;
	int cnt=0;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(dfn[v]==0)
		{
			if(!tarjan(v))
				return false;
			low[u]=min(low[u],low[v]);
		}
		else if(ind[u])
			low[u]=min(low[u],dfn[v]);
		cnt+=low[v]<dfn[u];
	}
	if(dfn[u]==low[u])
	{
		scc++;
		if(scc>1)
			return false;
		do
		{
			ind[stk[tot]]=false;
			tot--;
		}while(stk[tot+1]==u);
	}
	if(cnt>1)
		return false;
	return true;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
			adj[i].clear();
		for(int i=1,a,b;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			adj[a].push_back(b);
		}
		
		dfc=0;tot=0;scc=0;
		memset(dfn,0,sizeof dfn);
		memset(low,0,sizeof low);
		memset(ind,0,sizeof ind);
		
		bool flag=true;
		for(int i=0;i<n;i++)
			if(!dfn[i])
			{
				if(!tarjan(i))
				{flag=false;break;}
			}
		
		if(flag)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
