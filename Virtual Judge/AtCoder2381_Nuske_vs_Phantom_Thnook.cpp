#include<cstdio>
const int MAXN=2005;

int N,M,Q;
bool grid[MAXN][MAXN];

int V[MAXN][MAXN],E1[MAXN][MAXN],E2[MAXN][MAXN];

int main()
{
	scanf("%d%d%d",&N,&M,&Q);
	for(int i=1;i<=N;i++)
		for(int j=1,x;j<=M;j++)
		{
			scanf("%1d",&x);
			grid[i][j]=x;
		}
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			V[i][j]=V[i-1][j]+V[i][j-1]-V[i-1][j-1]+grid[i][j];
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			E1[i][j]=E1[i-1][j]+E1[i][j-1]-E1[i-1][j-1]+(grid[i][j]&&grid[i][j-1]);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			E2[i][j]=E2[i-1][j]+E2[i][j-1]-E2[i-1][j-1]+(grid[i][j]&&grid[i-1][j]);
	
	while(Q--)
	{
		int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		printf("%d\n",
		(V[x2][y2]-V[x2][y1-1]-V[x1-1][y2]+V[x1-1][y1-1])
		-(E1[x2][y2]-E1[x2][y1]-E1[x1-1][y2]+E1[x1-1][y1])
		-(E2[x2][y2]-E2[x2][y1-1]-E2[x1][y2]+E2[x1][y1-1]));
	}
	
	return 0;
}
