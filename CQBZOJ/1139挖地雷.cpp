#include<bits/stdc++.h>
#define MAXN 25
int n,num[MAXN],dp[MAXN],path[MAXN];
bool arr[MAXN][MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		dp[i]=num[i];
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			scanf("%d",&arr[i][j]);
	for(int i=n;i>0;i--)
		for(int j=i-1;j>0;j--)
			if(arr[j][i])
				if(dp[j]<dp[i]+num[j])
				{
					dp[j]=dp[i]+num[j];
					path[j]=i;
				}
	int ans=0,ans_k;
	for(int i=1;i<=n;i++)
		if(ans<dp[i])
		{ans=dp[i];ans_k=i;}
	printf("%d\n",ans);
	int x=ans_k;
	while(x)
	{
		printf("%d",x);
		if(path[x])printf(" ");else printf("\n");
		x=path[x];
	}
	return 0;
}
