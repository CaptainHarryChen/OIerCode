#include<cstdio>
#include<map>
using namespace std;
const long long MAXN=5000005LL;
long long sumu[MAXN];
int prime[MAXN],pcnt;
bool noprime[MAXN];
map<long long,long long>S;
void Init()
{
	noprime[1]=1;
	sumu[1]=1;
	for(int i=2;i<MAXN;i++)
	{
		if(!noprime[i])
		{
			prime[++pcnt]=i;
			sumu[i]=-1;
		}
		for(int j=1;j<=pcnt&&1LL*i*prime[j]<MAXN;j++)
		{
			noprime[i*prime[j]]=1;
			if(i%prime[j]==0)break;
			sumu[i*prime[j]]=-sumu[i];
		}
	}
	for(int i=2;i<MAXN;i++)
		sumu[i]+=sumu[i-1];
}
long long getsum(long long n)
{
	if(n<MAXN)
		return sumu[n];
	if(S.count(n))
		return S[n];
	long long ans=1,i=2;
	do
	{
		ans-=getsum(n/i)*(n/(n/i)-i+1);
		i=(n/(n/i))+1;
	}while(i<=n);
	return S[n]=ans;
}
int main()
{
	Init();
	long long a,b;
	scanf("%lld%lld",&a,&b);
	printf("%lld\n",getsum(b)-getsum(a-1));
	return 0;
}
