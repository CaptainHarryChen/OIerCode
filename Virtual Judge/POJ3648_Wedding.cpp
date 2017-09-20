#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=205;
vector<int>G[MAXN*2],rG[MAXN*2];
bool vis[MAXN*2];
int stack[MAXN*2],top;
int blkid[MAXN],blkc;
void dfs(int u)
{
	vis[u]=true;
	for(int i=0;i<(int)G[u].size();i++)
		if(!vis[G[u][i]])
			dfs(G[u][i]);
	stack[++top]=u;
}
void rdfs(int u)
{
	blkid[u]=blkc;
	for(int i=0;i<(int)rG[u].size();i++)
		if(!blkid[rG[u][i]])
			rdfs(rG[u][i]);
}
bool check(int n)
{
	memset(vis,0,sizeof vis);
	top=0;
	for(int i=0;i<n;i++)
		if(!vis[i])
			dfs(i);
	memset(blkid,0,sizeof blkid);
	blkc=0;
	while(top)
	{
		if(!blkid[stack[top]])
		{
			blkc++;
			rdfs(stack[top]);
		}
		top--;
	}
	for(int i=0;i<n;i++)
		if(blkid[i]==blkid[i^1])
			return false;
	return true;
}
int main()
{
	int n,m,a,b;
	char c,d;
	while(true)
	{
		scanf("%d%d",&n,&m);
		if(!n&&!m)
			break;
		for(int i=0;i<(n+1)*2;i++)
		{
			G[i].clear();
			rG[i].clear();
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d%c%d%c",&a,&c,&b,&d);
			a=a*2+(c=='h');
			b=b*2+(d=='h');
			if(a==0||b==0)
				continue;
			G[a].push_back(b^1);
			//G[a^1].push_back(b);
			G[b].push_back(a^1);
			//G[b^1].push_back(a);
			rG[b^1].push_back(a);
			//rG[a].push_back(b^1);
			rG[a^1].push_back(b);
			//rG[b].push_back(a^1);
		}
		G[n*2].push_back(1);
		G[n*2+1].push_back(1);
		G[0].push_back(n*2);
		G[0].push_back(n*2+1);
		rG[1].push_back(n*2);
		rG[1].push_back(n*2+1);
		rG[n*2].push_back(0);
		rG[n*2+1].push_back(0);
		n++;
		if(!check(n*2))
		{
			printf("bad luck\n");
			continue;
		}
		for(int i=1;i<n-2;i++)
			printf("%d%c ",i,blkid[i*2]>blkid[i*2+1]?'h':'w');
		printf("%d%c\n",n-2,blkid[(n-2)*2]>blkid[(n-2)*2+1]?'h':'w');
	}
	return 0;
}
