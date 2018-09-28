#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int N;
vector<int> adj[MAXN];
int val[MAXN],ans;

void dfs(int u,int fa=0)
{
	int mk=0;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(v==fa)
			continue;
		dfs(v,u);
		mk|=(val[u]&val[v]);
		val[u]|=val[v];
	}
	if(val[u]==0)
		val[u]=1;
	else
	{
		int id=0;
		while((1<<id)<mk||(val[u]&(1<<id)))
			id++;
		val[u]=((val[u]>>id)<<id)|(1<<id);
		ans=max(ans,id);
	}
	//printf("val[%d]=%d\n",u,val[u]);
}

int main()
{
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	dfs(1);
	printf("%d\n",ans);
	
	return 0;
}