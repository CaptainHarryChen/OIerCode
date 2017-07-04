#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 50005
int miu[MAXN],pri[MAXN],tot,sum[MAXN];
bool npri[MAXN];
long long solve(int a,int b)
{
	if(a>b)swap(a,b);
	int last=0;
	long long ret=0;
	for(int i=1;i<=a;i=last+1)
	{
		last=min(a/(a/i),b/(b/i));
		ret+=1LL*(a/i)*(b/i)*(sum[last]-sum[i-1]);
	}
	return ret;
}
int main()
{
	miu[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!npri[i])
		{
			pri[++tot]=i;
			miu[i]=-1;
		}
		for(int j=1;pri[j]*i<MAXN&&j<=tot;j++)
		{
			npri[pri[j]*i]=1;
			if(i%pri[j]==0)
			{
				miu[pri[j]*i]=0;
				break;
			}
			miu[i*pri[j]]=-miu[i];
		}
	}
	for(int i=1;i<MAXN;i++)
		sum[i]=sum[i-1]+miu[i];
	int cas,a,b,c,d,k;
	scanf("%d",&cas);
	while(cas--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		printf("%lld\n",solve(b/k,d/k)-solve((a-1)/k,d/k)-solve(b/k,(c-1)/k)+solve((a-1)/k,(c-1)/k));
	}
	return 0;
}
