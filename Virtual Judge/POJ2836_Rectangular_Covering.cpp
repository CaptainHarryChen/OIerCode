#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=18,MAXS=1<<15;
int n;
int P[MAXN][2];
int cov[MAXN][MAXN],S[MAXN][MAXN];
int dp[MAXS];
int main()
{
	int x1,y1,x2,y2,maxs;
	while(1)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		maxs=1<<n;
		for(int i=1;i<=n;i++)
			scanf("%d %d",P[i],P[i]+1);
		memset(cov,0,sizeof cov);
		memset(dp,0x7F,sizeof dp);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
				x1=min(P[i][0],P[j][0]);
				y1=min(P[i][1],P[j][1]);
				x2=max(P[i][0],P[j][0]);
				y2=max(P[i][1],P[j][1]);
				S[i][j]=max(1,x2-x1)*max(1,y2-y1);
				for(int k=1,bit=1;k<=n;k++,bit<<=1)
					if(x1<=P[k][0]&&P[k][0]<=x2
						&&y1<=P[k][1]&&P[k][1]<=y2)
						cov[i][j]+=bit;
			}
		dp[0]=0;
		for(int s=0;s<maxs;s++)
		{
			if(dp[s]==0x7F7F7F7F)
				continue;
			for(int i=1;i<=n;i++)
				for(int j=i;j<=n;j++)
					dp[s|cov[i][j]]=min(dp[s|cov[i][j]],dp[s]+S[i][j]);
		}
		printf("%d\n",dp[maxs-1]);
	}
	return 0;
}
