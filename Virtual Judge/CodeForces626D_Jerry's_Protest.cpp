#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=2005,MAXA=5005;

int n,a[MAXN];
double p[2][MAXA];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<i&&a[j]<a[i];j++)
			p[0][a[i]-a[j]]++;
	for(int i=1;i<MAXA;i++)
		p[0][i]/=n*(n-1)/2.0;
	for(int i=1;i<MAXA;i++)
		for(int j=1;j<MAXA-i;j++)
			p[1][i+j]+=p[0][i]*p[0][j];
	
	for(int i=1;i<MAXA;i++)
		p[1][i]+=p[1][i-1];
	double ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<i&&a[j]<a[i];j++)
			ans+=p[1][a[i]-a[j]-1];
	ans/=n*(n-1)/2.0;
	
	printf("%.10lf\n",ans);
	
	return 0;
}
