#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2000,MAXK=20;

int prime[MAXN],pcnt;
bool npr[MAXN];

int dp[MAXN][MAXK][MAXN];

int main()
{
	npr[1]=true;
	for(int i=2;i<MAXN;i++)
	{
		if(!npr[i])
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&1LL*prime[j]*i<MAXN;j++)
		{
			npr[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	
	dp[0][0][0]=1;
	for(int i=1;i<=pcnt;i++)
		for(int j=0;j<MAXK;j++)
			for(int k=0;k<MAXN;k++)
			{
				dp[i][j][k]=dp[i-1][j][k];
				if(k>=prime[i]&&j>0)
					dp[i][j][k]+=dp[i-1][j-1][k-prime[i]];
			}
	int n,k;
	for(;;)
	{
		scanf("%d%d",&n,&k);
		if(n==0&&k==0)
			break;
		printf("%d\n",dp[pcnt][k][n]);
	}
	
	return 0;
}
