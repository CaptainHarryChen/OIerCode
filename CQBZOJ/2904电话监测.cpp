#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 100100
#define INF 2147483647
using namespace std;
long long n,m,cnt;
struct pi
{
	int a,b;
}p[MAXN];
bool bol(pi a,pi b)
{
	return a.a<b.a;
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].a,&p[i].b);
	p[n+1].a=m+1;
	sort(p+1,p+n+2,bol);
	for(int i=0;i<=n+1;i++)
		if(p[i].b>p[i-1].b)
			cnt+=p[i].b-p[i-1].b;
	printf("%lld\n",cnt);
	return 0;
}
