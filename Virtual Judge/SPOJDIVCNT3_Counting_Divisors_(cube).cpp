#include<cstdio>
#include<cmath>
const int MAXN=316230*2;

long long n,sqr;
bool npr[MAXN];
int pr[MAXN],P;
int id1[MAXN],id2[MAXN],m;
long long w[MAXN],g[MAXN];

void LinerSieve()
{
	npr[1]=true;
	for(int i=2;i<MAXN;i++)
	{
		if(!npr[i])
			pr[++P]=i;
		for(int j=1;j<=P&&1LL*pr[j]*i<MAXN;j++)
		{
			npr[i*pr[j]]=true;
			if(i%pr[j]==0)
				break;
		}
	}
}
void Calc_g()
{
	m=0;
	for(long long i=1,j;i<=n;i=j+1)
	{
		j=n/(n/i);
		w[++m]=n/i;
		if(w[m]<=sqr)
			id1[w[m]]=m;
		else
			id2[n/w[m]]=m;
		g[m]=4LL*(w[m]-1);
	}
	for(int j=1;j<=P&&pr[j]<=sqr;j++)
		for(int i=1;i<=m&&1LL*pr[j]*pr[j]<=w[i];i++)
		{
			long long k=w[i]/pr[j];
			k=(k<=sqr)?id1[k]:id2[n/k];
			g[i]=g[i]-(g[k]-(j-1)*4);
		}
}
long long S(long long x,long long j)
{
	if(x<=1||x<pr[j])
		return 0;
	int y=(x<=sqr)?id1[x]:id2[n/x];
	long long res=g[y]-4LL*(j-1);
	for(int k=j;k<=P&&1LL*pr[k]*pr[k]<=x;k++)
	{
		long long t=pr[k];
		for(int e=1;1LL*pr[k]*t<=x;e++,t*=pr[k])
			res+=(3*e+1)*S(x/t,k+1)+(3*(e+1)+1);
	}
	return res;
}

int main()
{
	LinerSieve();
	Calc_g();
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld",&n);
		sqr=sqrt(n);
		Calc_g();
		printf("%lld\n",S(n,1)+1);
	}
	return 0;
}
