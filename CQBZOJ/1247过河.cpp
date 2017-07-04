#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXL 15000
int L,S,T,M,dp[MAXL],st[105];
bool stone[MAXL];
int main()
{
	scanf("%d%d%d%d",&L,&S,&T,&M);
	for(int i=1;i<=M;i++)
		scanf("%d",&st[i]);
	st[M+1]=L;
	sort(st+1,st+M+1);
	if(S==T)
	{
		int ans=0;
		for(int i=1;i<=M;i++)
			ans+=(st[i]%S==0);
		printf("%d\n",ans);
		return 0;
	}
	for(int i=1,d=0,x;i<=M+1;i++)
	{
		x=st[i]-d-st[i-1];
		if(x>100)
			d+=x-100;
		st[i]-=d;
		stone[st[i]]=1;
	}
	stone[st[M+1]]=0;
	memset(dp,0x7F,sizeof dp);
	dp[0]=0;
	for(int i=1;i<st[M+1]+T;i++)
	{
		for(int k=S;k<=T;k++)
			if(i>=k)
				dp[i]=min(dp[i],dp[i-k]);
		dp[i]+=stone[i];
	}
	int ans=0x7FFFFFFF;
	for(int i=st[M+1];i<st[M+1]+T;i++)
		ans=min(ans,dp[i]);
	printf("%d\n",ans);
	return 0;
}
