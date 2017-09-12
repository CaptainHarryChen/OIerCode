#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=5005,MAXM=50005;
vector<int>V[MAXN];
int stack[MAXN],top;
bool ind[MAXN];
int dfn[MAXN],dfc,low[MAXN];
int szans,ans[MAXN];
void dfs(int u)
{
	ind[u]=true;
	stack[++top]=u;
	dfn[u]=low[u]=++dfc;
	int sz=V[u].size();
	for(int p=0;p<sz;p++)
	{
		int v=V[u][p];
		if(!dfn[v])
		{
			dfs(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ind[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		int x;
		for(x=top;stack[x+1]!=u;x--)
			ind[stack[x]]=false;
		if(szans<top-x)
		{
			szans=top-x;
			for(int i=x+1;i<=top;i++)
				ans[i-x]=stack[i];
		}
		top=x;
	}
}
int main()
{
	int N,M;
	scanf("%d%d",&N,&M);
	int a,b,c;
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		V[a].push_back(b);
		if(c==2)
			V[b].push_back(a);
	}
	for(int i=1;i<=N;i++)
		if(!dfn[i])
			dfs(i);
	printf("%d\n",szans);
	sort(ans+1,ans+szans+1);
	for(int i=1;i<szans;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[szans]);
	return 0;
}
