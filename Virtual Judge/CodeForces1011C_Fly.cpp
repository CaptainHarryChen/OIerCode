#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=1005;

int n,m;
int a[MAXN],b[MAXN];

bool check(double fuel)
{
	double W=fuel+m;
	for(int i=1;i<=n;i++)
	{
		int u=i,v=(i==n?1:i+1);
		double delta=W/a[u];
		W-=delta;
		fuel-=delta;
		if(fuel<0)
			return false;
		delta=W/b[v];
		W-=delta;
		fuel-=delta;
		if(fuel<0)
			return false;
	}
	return true;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	
	double L=0,R=1e9+10;
	while(R-L>1e-6)
	{
		double mid=(L+R)/2.0;
		if(check(mid))
			R=mid;
		else
			L=mid;
	}
	if(L>1e9)
		puts("-1");
	else
		printf("%.10lf\n",L);
	
	return 0;
}
