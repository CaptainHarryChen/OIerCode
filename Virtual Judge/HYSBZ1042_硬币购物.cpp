#include<cstdio>
const long long MAXS=100005;

long long c[5],tot;
long long d[5],s;
long long dp[MAXS];

int main()
{
	scanf("%lld%lld%lld%lld%lld",c+1,c+2,c+3,c+4,&tot);
	dp[0]=1;
	for(long long i=1;i<=4;i++)
		for(long long j=c[i];j<MAXS;j++)
			dp[j]+=dp[j-c[i]];
	while(tot--)
	{
		scanf("%lld%lld%lld%lld%lld",d+1,d+2,d+3,d+4,&s);
		long long ans=0;
		for(long long st=0;st<(1<<4);st++)
		{
			long long flag=__builtin_popcount(st)%2==1?-1:1,sum=0;
			for(long long i=1;i<=4;i++)
				if(st&(1<<(i-1)))
					sum+=(d[i]+1)*c[i];
			if(s>=sum)
				ans+=flag*dp[s-sum];
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}
