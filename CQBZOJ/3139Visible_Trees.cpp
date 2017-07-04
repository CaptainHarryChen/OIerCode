#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
#define MAXN 100010
int T,a,b,prime[MAXN][20];
bool f_prime[MAXN];
void get_prime()
{
	for(int i=2;i<MAXN;i++)
		if(!f_prime[i])
		{
			prime[i][++prime[i][0]]=i;
			for(int j=i*2;j<MAXN;j+=i)
			{
				f_prime[j]=1;
				prime[j][++prime[j][0]]=i;
			}
		}
}
int solve(int num,int m)
{
	int len=prime[num][0],maxs=1<<len,ans=0;
	for(int s=1;s<maxs;s++)
	{
		int cnt=0,n=1;
		for(int i=0;i<len;i++)
			if(s&(1<<i))
			{
				cnt++;
				n*=prime[num][i+1];
			}
		if(cnt&1)
			ans+=m/n;
		else
			ans-=m/n;
	}
	return m-ans;
}
int main()
{
	get_prime();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&a,&b);
		if(a>b)swap(a,b);
		long long ans=b;
		for(int i=2;i<=a;i++)
		{
			ans+=solve(i,b);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
