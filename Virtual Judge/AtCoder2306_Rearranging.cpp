#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=2005;

int gcd(int a,int b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

int n,A[MAXN];
bool vis[MAXN];
vector<int> adj[MAXN],adj2[MAXN];
int deg[MAXN],ans[MAXN];
priority_queue<int> Q;

void dfs(int u)
{
	vis[u]=true;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(vis[v])
			continue;
		adj2[u].push_back(v);
		deg[v]++;
		dfs(v);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j&&gcd(A[i],A[j])>1)
				adj[i].push_back(j);
	for(int i=1;i<=n;i++)
		if(!vis[i])
			dfs(i);
	
	for(int i=1;i<=n;i++)
		if(deg[i]==0)
			Q.push(i);
	int it=0;
	while(!Q.empty())
	{
		int u=Q.top();
		ans[++it]=A[u];
		Q.pop();
		for(int i=0;i<(int)adj2[u].size();i++)
		{
			int v=adj2[u][i];
			deg[v]--;
			if(deg[v]==0)
				Q.push(v);
		}
	}
	
	for(int i=1;i<n;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
	
	return 0;
}
