#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=3005;

int n,A[MAXN];
vector<int> adj[MAXN];
bool st[MAXN];

void dfs(int u,int fa=0)
{
	st[u]=false;
	A[u]--;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(v==fa||A[v]>A[u])
			continue;
		dfs(v,u);
		if(st[v]==false)
		{
			st[u]=true;
			break;
		}
	}
	A[u]++;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
	{
		dfs(i);
		if(st[i])
			printf("%d ",i);
	}
	puts("");
	
	return 0;
}
