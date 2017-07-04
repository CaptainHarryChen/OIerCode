#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MAXN 10010
#define INF 2000000000
using namespace std;
struct rectangle
{
	long long x,y,w,h;
}arr[MAXN];
long long n,minx=INF,maxx=-INF;
long long check(long long k)
{
	long long lsum=0,rsum=0;
	for(int i=1;i<=n;i++)
	{
		if(arr[i].x+arr[i].w<=k)
			lsum+=(arr[i].w*arr[i].h);
		else if(arr[i].x>=k)
			rsum+=(arr[i].w*arr[i].h);
		else
		{
			lsum+=((k-arr[i].x)*arr[i].h);
			rsum+=((arr[i].x+arr[i].w-k)*arr[i].h);
		}
	}
	return lsum-rsum;
}
long long solve(long long l,long long r)
{
	if(l==r)return l;
	if(r-l==1)
	{
		if(abs(check(l))<=abs(check(r)))return l;
		return r;
	}
	long long mid=(l+r)>>1;
	if(check(mid)>=0)
		return solve(l,mid);
	else
		return solve(mid,r);
}
int main()
{
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld%lld",&arr[i].x,&arr[i].y,&arr[i].w,&arr[i].h);
		minx=min(minx,arr[i].x);
		maxx=max(maxx,arr[i].x+arr[i].w);
	}
	printf("%lld\n",solve(minx,maxx));
	return 0;
}
