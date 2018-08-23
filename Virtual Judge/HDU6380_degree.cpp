#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN=200005;

int N,K,M;
vector<int> adj[MAXN];
bool vis[MAXN];
int deg[MAXN];

void dfs(int u)
{
	vis[u]=true;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(!vis[v])
			dfs(v);
	}
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&N,&M,&K);
		for(int i=0;i<N;i++)
		{
			vis[i]=false;
			deg[i]=0;
			adj[i].clear();
		}
		for(int i=1;i<=M;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			adj[a].push_back(b);
			adj[b].push_back(a);
			deg[a]++;deg[b]++;
		}
		int cnt=0;
		for(int i=0;i<N;i++)
			if(!vis[i])
				dfs(i),cnt++;
		int mx=0,mxid=-1,ans;
		for(int i=0;i<N;i++)
			if(deg[i]>mx)
			{
				mx=deg[i];
				mxid=i;
			}
		ans=min(mx+cnt-1+K,N-1);
		printf("%d\n",ans);
	}
	
	return 0;
}
