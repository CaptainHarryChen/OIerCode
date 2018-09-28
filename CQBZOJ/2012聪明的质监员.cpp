#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005;

long long S;
int n,m;
int w[MAXN],v[MAXN];
int l[MAXN],r[MAXN];
long long sum1[MAXN],sumv[MAXN];

long long Calc(int W)
{
	for(int i=1;i<=n;i++)
	{
		sum1[i]=sum1[i-1]+(w[i]>=W?1:0);
		sumv[i]=sumv[i-1]+(w[i]>=W?v[i]:0);
	}
	long long res=0;
	for(int i=1;i<=m;i++)
		res+=(sum1[r[i]]-sum1[l[i]-1])*(sumv[r[i]]-sumv[l[i]-1]);
	return res;
}

int main()
{
	int L=0,R=0;
	scanf("%d%d%lld",&n,&m,&S);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&w[i],&v[i]);
		R=max(R,w[i]);
	}
	R++;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&l[i],&r[i]);
	
	while(L<R)
	{
		int mid=(L+R)/2;
		if(Calc(mid)>S)
			L=mid+1;
		else
			R=mid;
	}
	long long ans=min(S-Calc(L),Calc(L-1)-S);
	printf("%lld\n",ans);

	return 0;
}

