#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

void NoSolution()
{
	puts("NO");
	fclose(stdin);
	fclose(stdout);
	exit(0);
}

int n,A[MAXN];
vector<int> adj[MAXN];

int dfs(int u,int fa=0)
{
	if(adj[u].size()==1U)
		return A[u];
	long long sum=0;
	int tmp=0,mx=0;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(v==fa)
			continue;
		tmp=dfs(v,u);
		mx=max(mx,tmp);
		sum+=tmp;
	}
	if(fa==0)
	{
		if(sum%2==1||mx>sum/2||A[u]!=sum/2)
			NoSolution();
		return 0;
	}
	long long delta=sum-A[u];
	if(A[u]<delta||sum<A[u]||sum-mx<delta)
		NoSolution();
	return A[u]-delta;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	if(n==2)
	{
		if(A[1]==A[2])
			puts("YES");
		else
			puts("NO");
		return 0;
	}
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for(int i=1;i<=n;i++)
		if(adj[i].size()>1U)
		{
			dfs(i);
			break;
		}
	puts("YES");
	
	return 0;
}
