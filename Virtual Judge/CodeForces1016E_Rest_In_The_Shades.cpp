#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int sy,a,b,n,q;
pair<double,double> seg[MAXN];
double sum[MAXN];

int main()
{
	scanf("%d%d%d%d",&sy,&a,&b,&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&seg[i].first,&seg[i].second);
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+seg[i].second-seg[i].first;
	scanf("%d",&q);
	while(q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		double ans=0,k=1.0*(y-sy)/y;
		double lx=a+1.0*(x-a)*(-sy)/(y-sy),rx=b+1.0*(x-b)*(-sy)/(y-sy);
		int l=lower_bound(seg+1,seg+n+1,make_pair(lx,lx))-seg;
		int r=lower_bound(seg+1,seg+n+1,make_pair(rx,rx))-seg;
		r--;
		if(l<r)
			ans+=1.0*(sum[r-1]-sum[l-1])*k;
		if(l<=r)
			ans+=min(x+(seg[r].second-x)*k,1.0*b)-max(1.0*a,x+(seg[r].first-x)*k);
		l--;
		if(l>0&&seg[l].second>=lx)
			ans+=min(x+(seg[l].second-x)*k,1.0*b)-max(1.0*a,x+(seg[l].first-x)*k);
		printf("%.10lf\n",ans);
	}
	
	return 0;
}
