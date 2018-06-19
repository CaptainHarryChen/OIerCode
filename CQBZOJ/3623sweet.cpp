#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const long long MAXN=12,MAXA=10000005,MOD=2004;

long long n,a,b;
long long mi[MAXN];

long long C(long long n,long long m)
{
	if(n<m)return 0;
	long long md=MOD,fac=1;
	long long ret=1;
	for(long long i=1;i<=m;i++)
		fac*=i;
	md*=fac;
	for(long long i=n;i>n-m;i--)
		ret=(ret*i)%md;
	ret/=fac;
	ret%=MOD;
	return ret;
}
void dfs(long long i,long long p,long long j,long long m,long long &ans)
{
	if(i>n)
	{
		ans=(ans+p*C(n+m-j,n)%MOD+MOD)%MOD;
		return;
	}
	dfs(i+1,p,j,m,ans);
	dfs(i+1,-p,j+mi[i]+1,m,ans);
}

int main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	for(long long i=1;i<=n;i++)
		scanf("%lld",mi+i);
	
	long long ans1=0,ans2=0;
	dfs(1,1,0,a-1,ans1);
	dfs(1,1,0,b,ans2);
	printf("%lld\n",(ans2-ans1+MOD)%MOD);
	
	return 0;
}
