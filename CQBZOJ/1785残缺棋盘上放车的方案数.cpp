#include<cstdio>
#define MAXS 1500000
#define MAXN 23
int n,map[MAXN],cnt1[MAXN];
long long dp[MAXS];
int main()
{
	scanf("%d",&n);
	for(int i=1,si=1;i<=n;i++,si<<=1)
		for(int j=1,x;j<=n;j++)
		{
			scanf("%1d",&x);
			map[i]=map[i]*2+x;
		}
	int s=1<<n;
	dp[0]=1;
	for(int i=0,r,temp;i<s;i++)
	{
		r=0;
		for(int j=1,si=1;j<=n;j++,si<<=1)
			if(i&si)
				r++;
		temp=map[r]&i;
		for(int j=1,si=1;j<=n;j++,si<<=1)
			if(temp&si)
				dp[i]+=dp[i-si];
	}
	printf("%lld\n",dp[s-1]);
	return 0;
}
