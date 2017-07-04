#include<cstdio>
#include<cstring>
#define MAXN 21
bool edge[MAXN][MAXN],vis[MAXN],a[MAXN][MAXN];
int K,cnt,path[MAXN];
void dfs(int x,int k)
{
	vis[x]=1;
	path[k]=x;
	if(x==K)
	{
		for(int i=0;i<k;i++)
			printf("%d ",path[i]);
		printf("%d\n",path[k]);
		cnt++;
		vis[x]=0;
		return;
	}
	for(int i=1;i<MAXN;i++)
		if(edge[x][i]&&!vis[i])
			dfs(i,k+1);
	vis[x]=0;
}
bool check()
{
	memcpy(a,edge,sizeof a);
	for(int k=1;k<MAXN;k++)
		for(int i=1;i<MAXN;i++)
			for(int j=1;j<MAXN;j++)
				a[i][j]|=a[i][k]&&a[k][j];
	return a[1][K];
}
int main()
{
	for(int T=1;~scanf("%d",&K);T++)
	{
		memset(edge,0,sizeof edge);
		while(1)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			if(!a&&!b)break;
			edge[a][b]=1;
			edge[b][a]=1;
		}
		if(K==1)
		{
			printf("CASE %d:\n",T);
			printf(" 1\n");
			printf("There are 1 routes from the firestation to streetcorner 1.\n");
			continue;
		}
		printf("CASE %d:\n",T);
		memset(vis,0,sizeof vis);
		cnt=0;
		if(check())
			dfs(1,0);
		printf("There are %d routes from the firestation to streetcorner %d.\n",cnt,K);
	}
	return 0;
}
