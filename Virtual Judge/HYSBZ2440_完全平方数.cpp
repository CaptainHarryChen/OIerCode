#include<cstdio>
#include<cmath>
#define MAXP 10000000
bool noprime[MAXP];
int prime[MAXP/6],pcnt;
int mu[MAXP];
int main()
{
	noprime[1]=1;mu[1]=1;
	for(int i=1;i<MAXP;i++)
	{
		if(!noprime[i])
		{
			prime[++pcnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=pcnt&&i*prime[j]<MAXP;j++)
		{
			noprime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	int T,k;
	long long l,r,mid,cnt;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&k);
		l=1LL;r=10000000000LL;
		while(l<r)
		{
			mid=(l+r)>>1LL;
			cnt=0LL;
			if(mid<20)
			{mid++;mid--;}
			for(long long i=1LL;i<=1LL*sqrt(mid);i++)
				cnt+=1LL*mu[i]*(mid/(i*i));
			if(cnt>=k)
				r=mid;
			else
				l=mid+1LL;
		}
		printf("%lld\n",l);
	}
	return 0;
}
