#include<cstdio>
#include<set>
#include<vector>
using namespace std;
const int MAXN=1000005;

int n,m;
vector<int> adj[MAXN],ans;
set<int> rem;
bool use[MAXN];

void dfs(int u)
{
	rem.erase(u);
	for(int i=0;i<(int)adj[u].size();i++)
		rem.erase(adj[u][i]);
	if(!rem.empty())
		dfs(*rem.begin());
	if(!use[u])
	{
		use[u]=true;
		for(int i=0;i<(int)adj[u].size();i++)
			use[adj[u][i]]=true;
		ans.push_back(u);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		adj[a].push_back(b);
	}
	for(int i=1;i<=n;i++)
		rem.insert(i);
	dfs(1);
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)
		printf("%d ",ans[i]);
	puts("");
	
	return 0;
}
