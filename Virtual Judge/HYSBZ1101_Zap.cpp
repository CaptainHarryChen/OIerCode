#include<cstdio>
const int MAXN=50005;
int mu[MAXN],prime[MAXN/3],pcnt;
bool nprime[MAXN];
void Init()
{
	nprime[1]=1;
	mu[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!nprime[i])
		{
			prime[++pcnt]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=pcnt&&i*prime[j]<MAXN;j++)
		{
			nprime[i*prime[j]]=1;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	for(int i=1;i<MAXN;i++)
		mu[i]+=mu[i-1];
}
int solve(int a,int b,int d)
{
	a/=d;b/=d;
	if(a>b)
	{
		a^=b;
		b^=a;
		a^=b;
	}
	int ret=0,last;
	for(int i=1;i<=a;i=last+1)
	{
		if(a/(a/i)>b/(b/i))
			last=b/(b/i);
		else
			last=a/(a/i);
		ret+=(a/i)*(b/i)*(mu[last]-mu[i-1]);
	}
	return ret;
}
int main()
{
	Init();
	int n,a,b,d;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d%d",&a,&b,&d);
		printf("%d\n",solve(a,b,d));
	}
	return 0;
}
