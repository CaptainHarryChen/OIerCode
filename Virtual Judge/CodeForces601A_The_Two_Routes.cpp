#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=405;
int n,m;
int G[MAXN][MAXN];
int main()
{
	int a,b;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		G[a][b]=1;
		G[b][a]=1;
	}
	int type=G[1][n];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)
				G[i][j]=(G[i][j]!=type?1:0x3FFFFFFF);
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				G[i][j]=min(G[i][j],G[i][k]+G[k][j]);
	if(G[1][n]==0x3FFFFFFF)
		puts("-1");
	else
		printf("%d\n",G[1][n]);
	return 0;
}
