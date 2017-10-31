#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=55,MAXT=2505;
int N,M,T;
int bor[MAXN][MAXN];
int best[MAXN][MAXT],dp1[MAXN][MAXT][2],dp2[MAXN][MAXT];
void DP1(int id)
{
	int cnt[2]={0};
	for(int i=1;i<=M;i++)
	{
		dp1[i][0][0]=dp1[i][0][1]=0;
		cnt[bor[id][i]]++;
		dp1[i][1][0]=cnt[0];
		dp1[i][1][1]=cnt[1];
		for(int j=2;j<=T&&j<=i;j++)
		{
			dp1[i][j][0]=max(dp1[i-1][j][0]+(bor[id][i]==0),dp1[i-1][j-1][1]+1);
			dp1[i][j][1]=max(dp1[i-1][j][1]+(bor[id][i]==1),dp1[i-1][j-1][0]+1);
		}
	}
	for(int j=0;j<=T;j++)
		best[id][j]=max(dp1[M][j][0],dp1[M][j][1]);
}
void DP2()
{
	for(int i=1;i<=N;i++)
		for(int j=0;j<=T;j++)
			for(int k=0;k<=j&&k<=M;k++)
				dp2[i][j]=max(dp2[i][j],dp2[i-1][j-k]+best[i][k]);
}
int main()
{
	scanf("%d%d%d",&N,&M,&T);
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=M;j++)
			scanf("%1d",&bor[i][j]);
		DP1(i);
	}
	DP2();
	printf("%d\n",dp2[N][T]);
	return 0;
}
