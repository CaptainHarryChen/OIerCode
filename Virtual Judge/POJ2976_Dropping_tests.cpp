#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1005;
typedef pair<double,double> test;
int n,k;
test t[MAXN];
double x;
bool cmp(test a,test b)
{
	return a.first-a.second*x<b.first-b.second*x;
}
int main()
{
	while(scanf("%d%d",&n,&k),n||k)
	{
		for(int i=1;i<=n;i++)
			scanf("%lf",&t[i].first);
		for(int i=1;i<=n;i++)
			scanf("%lf",&t[i].second);
		double l=0.0,r=1.0,mid,sum=0.0;
		while(r-l>=1e-5)
		{
			mid=(l+r)/2.0;
			x=mid;
			sort(t+1,t+n+1,cmp);
			sum=0.0;
			for(int i=k+1;i<=n;i++)
				sum+=t[i].first-t[i].second*x;
			if(sum>=0.0)
				l=mid;
			else
				r=mid;
		}
		printf("%.0lf\n",(l+r)/2.0*100.0);
	}
	return 0;
}
