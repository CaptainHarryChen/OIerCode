#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=100005;

int N;
vector<int> adj[MAXN];
int sg[MAXN];

void dfs(int u,int fa=0)
{
	for(auto v:adj[u])
	{
		if(v==fa)
			continue;
		dfs(v,u);
		sg[u]^=(sg[v]+1);
	}
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1);
	if(sg[1])
		puts("Alice");
	else
		puts("Bob");
	
	return 0;
}
