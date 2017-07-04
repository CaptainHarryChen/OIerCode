#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 100005
#define MAXV 2000000
#define lowbit(a) (a&(-a))
long long n,l,c,speed[MAXN];
long long ans;
long long sum[MAXV+10];
void update(long long x)
{
	while(x<=MAXV)
	{
		sum[x]++;
		x+=lowbit(x);
	}
}

long long query(long long x)
{
	long long ret=0;
	while(x)
	{
		ret+=sum[x];
		x-=lowbit(x);
	}
	return ret;
}
int main()
{
	scanf("%lld%lld%lld",&n,&l,&c);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&speed[i]);
	sort(speed+1,speed+n+1);
	double cir;
	long long temp;
	long long s=0;
	for(long long i=1;i<=n;i++)
	{
		cir=(double)l*speed[i]/speed[n];
		temp=(long long)((cir-(long long)cir)*MAXV);
		ans+=((long long)cir-1)*(long long)(i-1)-s+query(temp+2);
		update(temp+1);
		s+=(long long)cir;
	}
	printf("%lld\n",ans);
	return 0;
}
