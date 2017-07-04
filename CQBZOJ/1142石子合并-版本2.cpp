#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 205
int N,num[MAXN],dp[MAXN][MAXN],sum[MAXN];
int main()
{
    cin>>N;
    memset(dp,127,sizeof dp);
    for(int i=1;i<=N;i++)
    {
        cin>>num[i];
        dp[i][i]=num[i];
        sum[i]=sum[i-1]+num[i];
    }
	for(int i=N+1;i<2*N;i++)
    {
        num[i]=num[i-N];
        dp[i][i]=num[i];
        sum[i]=sum[i-1]+num[i];
    }
    for(int l=1;l<N;l++)
        for(int i=1,j=i+l;j<=2*N-1;i++,j++)
            for(int k=i;k<j;k++)
                if(dp[i][j]>dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1])
                    dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
	int mindp=999999999;
	for(int i=1;i<=N;i++)
		mindp=min(mindp,dp[i][i+N-1]);
	cout<<mindp-sum[N]<<endl;
	memset(dp,0,sizeof dp);
	for(int i=1;i<=2*N;i++)
		dp[i][i]=num[i];
	for(int l=1;l<N;l++)
        for(int i=1,j=i+l;j<=N*2-1;i++,j++)
            for(int k=i;k<j;k++)
                if(dp[i][j]<dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1])
                    dp[i][j]=dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1];
    int maxdp=0;
	for(int i=1;i<=N;i++)
		maxdp=max(maxdp,dp[i][i+N-1]);
	cout<<maxdp-sum[N]<<endl;
    return 0;
}