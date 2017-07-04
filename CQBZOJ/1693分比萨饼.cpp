#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#define MAXN 10010
#define pp 0.000001
#define INF 2000000000
using namespace std;
int T,N,F;
double s[MAXN];
double count(double x)
{
	int cnt=0;
	for(int i=1;i<=N;i++)
		cnt+=(int)(s[i]/x);
	return cnt;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&F);
		F++;
		double l=0,r=INF,mid,x;
		for(int i=1;i<=N;i++)
		{
			scanf("%lf",&x);
			s[i]=x*x;
			r=max(s[i],r);
		}
		while(1)
		{
			mid=(l+r)/2;
			if((r-l)<pp)break;
			if(count(mid)<F)
				r=mid;
			else
				l=mid;
		}
		printf("%.4lf\n",mid*M_PI);
	}
	return 0;
}
