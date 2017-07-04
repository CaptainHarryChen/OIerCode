#include<cstdio>
const int MAXP=1<<20;
bool noprime[MAXP];
int prime[MAXP],pcnt;
int Pfacs[MAXP];
int main()
{
	noprime[1]=1;
	for(int i=2;i<MAXP;i++)
	{
		if(!noprime[i])
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt;j++)
		{
			if(i*prime[j]>=MAXP)
				break;
			noprime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
		}
	}
	int n;
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=pcnt;i++)
			Pfacs[i]=0;
		int cnt=0;
		long long ans=1LL;
		for(int i=1;i<=pcnt&&n>1;i++)
			while(n%prime[i]==0)
			{
				cnt++;
				Pfacs[i]++;
				ans*=1LL*cnt;
				ans/=Pfacs[i];
				n/=prime[i];
			}
		printf("%d %lld\n",cnt,ans);
	}
	return 0;
}
