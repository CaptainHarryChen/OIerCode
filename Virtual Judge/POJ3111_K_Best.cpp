#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
typedef pair<double,double> jewel;
int n,k;
pair<int,jewel> jes[MAXN];
double cmpX;
bool cmp(pair<int,jewel> a,pair<int,jewel> b)
{
	return a.second.first-cmpX*a.second.second>
	b.second.first-cmpX*b.second.second;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		jes[i].first=i;
		scanf("%lf%lf",&jes[i].second.first,&jes[i].second.second);
	}
	double L=0.0,R=1e7,mid,sum;
	while(R-L>1e-6)
	{
		mid=(R+L)/2.0;
		cmpX=mid;
		sort(jes+1,jes+n+1,cmp);
		sum=0.0;
		for(int i=1;i<=k;i++)
			sum+=jes[i].second.first-jes[i].second.second*mid;
		if(sum>=0.0)
			L=mid;
		else
			R=mid;
	}
	for(int i=1;i<k;i++)
		printf("%d ",jes[i].first);
	printf("%d\n",jes[k].first);
	return 0;
}
