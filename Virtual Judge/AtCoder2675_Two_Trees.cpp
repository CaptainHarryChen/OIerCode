#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=100005;

int N;
int rt1,rt2;
vector<int> adj1[MAXN],adj2[MAXN],adj[MAXN];
int stk[MAXN],tp;
bool vis[MAXN];
int ans[MAXN];

void dfs(int u,const vector<int> G[])
{
	for(auto v:G[u])
		dfs(v,G);
	if((G[u].size()&1)==0)
		stk[++tp]=u;
	while(tp>=2)
	{
		adj[stk[tp]].push_back(stk[tp-1]);
		adj[stk[tp-1]].push_back(stk[tp]);
		tp-=2;
	}
}
void Mark(int u,int val=1)
{
	vis[u]=true;
	ans[u]=val;
	for(auto v:adj[u])
	{
		if(vis[v])
			continue;
		Mark(v,-val);
	}
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		int f;
		scanf("%d",&f);
		if(f==-1)
			rt1=i;
		else
			adj1[f].push_back(i);
	}
	for(int i=1;i<=N;i++)
	{
		int f;
		scanf("%d",&f);
		if(f==-1)
			rt2=i;
		else
			adj2[f].push_back(i);
	}
	for(int i=1;i<=N;i++)
		if((adj1[i].size()&1)!=(adj2[i].size()&1))
		{
			puts("IMPOSSIBLE");
			return 0;
		}
	puts("POSSIBLE");
	tp=0;
	dfs(rt1,adj1);
	tp=0;
	dfs(rt2,adj2);
	for(int i=1;i<=N;i++)
		if(!vis[i])
			Mark(i);
	for(int i=1;i<=N;i++)
	{
		if(adj1[i].size()&1)
			printf("0 ");
		else
			printf("%d ",ans[i]);
	}
	puts("");
	
	return 0;
}
