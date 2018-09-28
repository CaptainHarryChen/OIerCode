#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=100005;

int N,K;
int nxt[MAXN],dep[MAXN];
vector<int> radj[MAXN];
int ans=0;

void dfs(int u)
{
	for(auto v:radj[u])
	{
		dfs(v);
		dep[u]=max(dep[v]+1,dep[u]);
	}
	if(dep[u]==K-1&&nxt[u]!=1)
	{
		ans++;
		dep[u]=-1;
	}
}

int main()
{
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&nxt[i]);
		if(i==1&&nxt[i]!=1)
		{
			nxt[i]=1;
			ans++;
			continue;
		}
		if(i!=1)
			radj[nxt[i]].push_back(i);
	}
	dfs(1);
	printf("%d\n",ans);
	
	return 0;
}
