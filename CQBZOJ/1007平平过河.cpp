#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXL 101005
#define MAXN 210
int l,n,m,s,t;
int arr[MAXN][MAXN];
int stone[MAXN];
int dp[MAXN][MAXN];
int main()
{
	scanf("%d%d%d%d%d",&l,&n,&m,&s,&t);
	stone[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&stone[i]);
	for(int i=n+1;i<n+t;i++)
		stone[i]=l+i-n;
	for(int i=0;i<n+t;i++)
		for(int j=i+1;j<n+t;j++)
		{
			arr[i][j]=(stone[j]-stone[i]+t-1)/t;
			if(t*arr[i][j]>=stone[j]-stone[i]&&s*arr[i][j]<=stone[j]-stone[i]);
			else arr[i][j]=0x3FFFFFFF;
		}
	for(int i=1;i<n+t;i++)
	{
		dp[i][1]=arr[0][i];
		for(int j=2;j<=i&&j<=n+1;j++)
		{
			dp[i][j]=0x3FFFFFFF;
			for(int k=j-1;k<i&&k<=n;k++)
				dp[i][j]=min(dp[k][j-1]+arr[k][i],dp[i][j]);
		}
	}
	int ans=0x3FFFFFFF;
	for(int i=n+1;i<n+t;i++)
		for(int j=1;j<=i&&j<=n+1;j++)
			if(dp[i][j]-j<=m)
				ans=min(ans,dp[i][j]);
	if(ans<0x3FFFFFFF)
		printf("%d\n",ans);
	else
	{
		ans=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=i&&j<=n+1;j++)
				if(dp[i][j]-j<=m)
					ans=max(ans,stone[i]+t*(m-(dp[i][j]-j)));
		ans=max(ans,t*m);
		printf("%d\n",ans);
	}
	return 0;
}
