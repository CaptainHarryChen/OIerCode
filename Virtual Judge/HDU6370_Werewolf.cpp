#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN=100005;

int dsu[MAXN];
int Root(int u)
{return dsu[u]==0?u:(dsu[u]=Root(dsu[u]));}
void Merge(int u,int v)
{
	int r1=Root(u),r2=Root(v);
	if(r1==r2)return;
	dsu[r1]=r2;
}

int n,ans,nxt[MAXN];
int deg[MAXN],siz[MAXN];
bool vis[MAXN],mk[MAXN];
vector<pair<int,int> > wolf;
vector<int> adj[MAXN];

void dfs(int u)
{
	vis[u]=true;
	siz[u]++;
	if(nxt[u])
	{
		siz[nxt[u]]+=siz[u];
		Merge(u,nxt[u]);
		if(!vis[nxt[u]])
			dfs(nxt[u]);
	}
}
void Mark(int u)
{
	mk[u]=true;
	ans++;
	for(int i=0;i<(int)adj[u].size();i++)
		if(!mk[adj[u][i]])
			Mark(adj[u][i]);
}

int main()
{
	int T;
	char str[20];
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		
		for(int i=1;i<=n;i++)
		{
			adj[i].clear();
			deg[i]=0;
			siz[i]=0;
			dsu[i]=0;
			mk[i]=0;
			vis[i]=0;
			nxt[i]=0;
		}
		ans=0;
		wolf.clear();
		
		for(int i=1,x;i<=n;i++)
		{
			scanf("%d%s",&x,str);
			if(str[0]=='v')
			{
				nxt[i]=x;
				adj[x].push_back(i);
				deg[x]++;
			}
			else
				wolf.push_back(make_pair(i,x));
		}
		for(int i=1;i<=n;i++)
			if(deg[i]==0&&!vis[i])
				dfs(i);
		for(int i=1;i<=n;i++)
			if(!vis[i])
				dfs(i);
		for(int i=0;i<(int)wolf.size();i++)
		{
			int u=wolf[i].first,v=wolf[i].second;
			if(Root(u)==Root(v))
			{
				if(!mk[v])
					Mark(v);
			}
		}
		printf("0 %d\n",ans);
	}
	return 0;
}
