#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const long long prime[11]={0,2,3,5,7,11,13,17,19,23,29};
long long a,b;
long long cnt,ans,best;
void dfs(long long s,long long now,long long step,long long x)
{
	if(now>b)return;
	if(now>=a&&now<=b)
	{
		if(x*(step+1)>best)
		{best=x*(step+1);ans=now;}
		else if(x*(step+1)==best&&now<ans) ans=now;
	}
	for(long long i=s;i<=10;i++)
		if(i==s)dfs(i,now*prime[i],step+1,x);
		else dfs(i,now*prime[i],1,x*(step+1));
}
int main()
{
	scanf("%lld%lld",&a,&b);
	if(b<=100000L)
	{
		for(long long i=a;i<=b;i++)
		{
			cnt=0;
			long long n=i;
			for(long long j=1;j*j<=i;j++)
				if(n%j==0)
				{
					cnt++;
					if(j!=n/j)cnt++;
				}
			if(cnt>best)
			{best=cnt;ans=i;}
		}
	}
	else
		dfs(1,1,0,1);
	printf("%lld\n",ans);
	return 0;
}
