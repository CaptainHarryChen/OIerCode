#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000010;

int prime[MAXN],pcnt;
bool npr[MAXN];

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
	
	int N;
	scanf("%d",&N);
	while(N--)
	{
		long long L,U,ans=0;
		scanf("%lld%lld",&L,&U);
		for(int i=1;i<=pcnt;i++)
		{
			long long x=1LL*prime[i]*prime[i];
			while(x<L)
				x*=prime[i];
			while(x<=U)
			{
				ans++;
				x*=prime[i];
			}
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}