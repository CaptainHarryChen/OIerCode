#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN=505,MAXM=MAXN*MAXN/2;
int G[MAXN][MAXN];
int edge[MAXM][3];
int cnt[MAXN][MAXN],ans[MAXN][MAXN];
int main()
{
	int n,m,a,b,c;
	scanf("%d%d",&n,&m);
	memset(G,0x3F,sizeof G);
	for(int i=1;i<=n;i++)
		G[i][i]=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		G[a][b]=G[b][a]=c;
		edge[i][0]=a;edge[i][1]=b;edge[i][2]=c;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			if(G[edge[i][0]][j]==G[edge[i][1]][j]+edge[i][2])
				cnt[edge[i][0]][j]++;
			if(G[edge[i][1]][j]==G[edge[i][0]][j]+edge[i][2])
				cnt[edge[i][1]][j]++;
		}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(G[i][j]==G[i][k]+G[k][j])
					ans[i][j]+=cnt[k][i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			printf("%d ",ans[i][j]);
	puts("");
	return 0; 
}
