#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=505,MAXM=20005;
int G[MAXN][MAXN];
int E[MAXN][3];
int main()
{
	int n,m,a,b,w;
	scanf("%d%d",&n,&m);
	memset(G,0x3F,sizeof G);
	for(int i=1;i<=n;i++)
		G[i][i]=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&w);
		G[a][b]=min(G[a][b],w);
		G[b][a]=min(G[b][a],w);
		E[i][0]=a;E[i][1]=b;E[i][2]=w;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
		{
			if(i==k)continue;
			for(int j=1;j<=n;j++)
			{
				if(j==i||j==k)continue;
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
			}
		}
	int mn=0x7FFFFFFF,id;
	for(int i=1;i<=m;i++)
	{
		if(mn>G[1][E[i][0]]+E[i][2]/2+G[E[i][1]][n]
			||mn>G[1][E[i][1]]+E[i][2]/2+G[E[i][0]][n])
		{
			mn=min(G[1][E[i][0]]+E[i][2]/2+G[E[i][1]][n],
				G[1][E[i][1]]+E[i][2]/2+G[E[i][0]][n]);
			id=i;
		}
	}
	printf("%d %d\n%d\n",E[id][0],E[id][1],mn);
	return 0;
}
