#include<cstdio>
#define MOD 1000000000000000000LL
int N,K;
struct superlong
{
	long long a;
	long long b;
	superlong(){a=b=0;}
	void operator = (int t)
	{
		a=0;b=t;
	}
	void operator += (superlong t)
	{
		b+=t.b;
		if(b>=MOD)
		{
			b-=MOD;
			a+=1;
		}
		a+=t.a;
	}
	void print()
	{
		if(a)
			printf("%lld%018lld\n",a,b);
		else
			printf("%lld\n",b);
	}
}dp[105][1005];
int main()
{
	scanf("%d%d",&N,&K);
	dp[0][0]=1;
	for(int i=1;i<=K;i++)
	{
		dp[i][0]=1;
		for(int j=1;j<=N;j++)
			for(int k=0;k*i<=j;k++)
				dp[i][j]+=dp[i-1][j-k*i];
	}
	dp[K][N].print();
	return 0;
}
