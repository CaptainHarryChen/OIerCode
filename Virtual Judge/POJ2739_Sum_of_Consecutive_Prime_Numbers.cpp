#include<cstdio>
const int MAXN=10010;
bool noprime[MAXN];
int prime[1240],pcnt;
void getprime()
{
	noprime[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!noprime[i])
			prime[++pcnt]=i;
		for(int j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
		{
			noprime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
		}
	}
}
int solve(int n)
{
	int ret=0;
	int l=1,r=1,sum=2;
	while(prime[r]<=n)
	{
		if(sum==n)
		{
			ret++;
			r++;
			sum+=prime[r];
		}
		else if(sum<n)
		{
			r++;
			sum+=prime[r];
		}
		else
		{
			sum-=prime[l];
			l++;
		}
	}
	return ret;
}
int main()
{
	getprime();
	int n;
	while(1)
	{
		scanf("%d",&n);
		if(!n)break;
		printf("%d\n",solve(n));
	}
	return 0;
}
