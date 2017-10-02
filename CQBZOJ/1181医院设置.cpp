#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=105;
int val[MAXN],son[MAXN][2],fa[MAXN];
int ans=0x7FFFFFFF,sum;
bool vis[MAXN];
void dfs(int u,int lev=0)
{
	if(u==0||vis[u])return;
	vis[u]=true;
	if(sum>=ans)return;
	sum+=lev*val[u];
	dfs(son[u][0],lev+1);
	dfs(son[u][1],lev+1);
	dfs(fa[u],lev+1);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",val+i,son[i],son[i]+1);
		fa[son[i][0]]=i;
		fa[son[i][1]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof vis);
		sum=0;
		dfs(i);
		ans=min(ans,sum);
	}
	printf("%d\n",ans);
	return 0;
}
