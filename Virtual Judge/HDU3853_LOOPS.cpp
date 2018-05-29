#include<cstdio>
const int MAXN=1005;
const int dir[3][2]={{0,0},{0,1},{1,0}};

int R,C;
double P[MAXN][MAXN][3];
double dp[MAXN][MAXN];

int main()
{
	while(scanf("%d%d",&R,&C)!=EOF)
	{
		for(int i=1;i<=R;i++)
			for(int j=1;j<=C;j++)
				for(int k=0;k<3;k++)
					scanf("%lf",&P[i][j][k]);
		
		dp[R][C]=0;
		for(int i=R;i>0;i--)
			for(int j=C;j>0;j--)
			{
				if(i==R&&j==C)
					continue;
				if(P[i][j][0]==1)
					continue;
				dp[i][j]=(dp[i+1][j]*P[i][j][2]+dp[i][j+1]*P[i][j][1]+2)/(1-P[i][j][0]);
			}
			
		printf("%.3lf\n",dp[1][1]);
	}
	
	return 0;
}
