#include<cstdio>
#include<unordered_set>
#include<algorithm>
using namespace std;
const int MAXN=10010;

int prime[MAXN],pcnt;
long long sum[MAXN];
bool npr[MAXN];
unordered_set<long long> S;

int main()
{
	npr[1]=true;
	for(int i=2;i<MAXN;i++)
	{
		if(!npr[i])
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&1LL*prime[j]*i<MAXN;j++)
		{
			npr[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	for(int i=1;i<=pcnt;i++)
		sum[i]=sum[i-1]+prime[i];
	
	int n;
	for(;;)
	{
		scanf("%d",&n);
		if(n==0)
			break;
		int ans=0;
		S.clear();
		for(int i=0;prime[i]<=n;i++)
		{
			S.insert(sum[i]);
			if(S.count(sum[i]-n))
				ans++;
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
