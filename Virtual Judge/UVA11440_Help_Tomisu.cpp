#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=10000010,MOD=100000007;

int PowMod(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1LL*res*a%MOD;
		a=1LL*a*a%MOD;
		b>>=1;
	}
	return res;
}

int prime[MAXN],pcnt;
int fac[MAXN],ifac[MAXN],inv[MAXN];
int tmp[MAXN];
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
	fac[0]=1;
	for(int i=1;i<MAXN;i++)
		fac[i]=1LL*fac[i-1]*i%MOD;
	ifac[MAXN-1]=PowMod(fac[MAXN-1],MOD-2);
	for(int i=MAXN-2;i>=0;i--)
		ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;
	for(int i=1;i<MAXN;i++)
		inv[i]=1LL*ifac[i]*fac[i-1]%MOD;
	
	tmp[0]=1;
	for(int i=1;i<=pcnt;i++)
		tmp[i]=1LL*tmp[i-1]*inv[prime[i]]%MOD*(prime[i]-1)%MOD;
	
	int n,m;
	for(;;)
	{
		scanf("%d%d",&n,&m);
		if(n==0&&m==0)
			break;
		int pos=upper_bound(prime+1,prime+pcnt+1,m)-prime;
		int ans=1LL*fac[n]*tmp[pos-1]%MOD;
		printf("%d\n",(ans+MOD-1)%MOD);
	}
	
	return 0;
}
