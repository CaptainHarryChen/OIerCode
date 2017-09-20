#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN=1030,MAXM=2050;
vector<int>G[MAXN*2],rG[MAXN*2];
int other[MAXN*2];
bool vis[MAXN*2];
int st[MAXN*2],top;
int blkid[MAXN*2],blkc;
void dfs(int u)
{
	vis[u]=true;
	for(int i=0;i<G[u].size();i++)
		if(!vis[G[u][i]])
			dfs(G[u][i]);
	st[++top]=u;
}
bool rdfs(int u)
{
	blkid[u]=blkc;
	if(blkid[other[u]]==blkc)
		return false;
	for(int i=0;i<rG[u].size();i++)
		if(!blkid[rG[u][i]])
			if(!rdfs(rG[u][i]))
				return false;
	return true;
}
bool check(int N)
{
	memset(vis,0,sizeof vis);
	top=0;
	for(int i=0;i<N*2;i++)
		if(!vis[i])
			dfs(i);
	memset(blkid,0,sizeof blkid);
	blkc=0;
	while(top)
	{
		if(!blkid[st[top]])
		{
			blkc++;
			if(!rdfs(st[top]))
				return false;
		}
		top--;
	}
	return true;
}
int main()
{
	int N,M,a,b,ans;
	while(true)
	{
		scanf("%d%d",&N,&M);
		if(!N&&!M)
			break;
		for(int i=1;i<=N;i++)
		{
			scanf("%d%d",&a,&b);
			other[a]=b;
			other[b]=a;
		}
		for(int i=0;i<2*N;i++)
		{
			G[i].clear();
			rG[i].clear();
		}
		ans=M;
		for(int i=1;i<=M;i++)
		{
			scanf("%d%d",&a,&b);
			G[other[a]].push_back(b);
			G[other[b]].push_back(a);
			rG[b].push_back(other[a]);
			rG[a].push_back(other[b]);
			if(!check(N))
			{
				ans=i-1;
				i++;
				while(i<=M)
				{
					scanf("%d%d",&a,&b);
					i++;
				}
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
