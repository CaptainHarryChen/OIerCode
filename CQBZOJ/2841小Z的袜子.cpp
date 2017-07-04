#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXN 50005
long long n,m,num[MAXN];
long long pos[MAXN],cnts[MAXN];
struct Quary
{
	long long l,r,id;
}Q[MAXN];
long long ans[MAXN][2];
bool cmp(Quary a,Quary b)
{return pos[a.l]<pos[b.l]||(pos[a.l]==pos[b.l]&&a.r<b.r);}
long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}
void init();
void solve();
void print();
int main()
{
	init();
	solve();
	print();
	return 0;
}
void init()
{
	scanf("%lld%lld",&n,&m);
	for(long long i=1;i<=n;i++)
		scanf("%lld",&num[i]);
	for(long long i=1;i<=m;i++)
	{
		scanf("%lld%lld",&Q[i].l,&Q[i].r);
		Q[i].id=i;
	}
	long long block=sqrt(n);
	for(long long i=1;i<=n;i++)
		pos[i]=(i-1)/block+1;
	sort(Q+1,Q+m+1,cmp);
}
void solve()
{
	long long sum=0;
	for(long long l=1,r=0,i=1;i<=m;i++)
	{
		while(r<Q[i].r)
		{
			sum-=(cnts[num[r+1]]*cnts[num[r+1]]);
			cnts[num[r+1]]++;
			sum+=(cnts[num[r+1]]*cnts[num[r+1]]);
			r++;
		}
		while(r>Q[i].r)
		{
			sum-=(cnts[num[r]]*cnts[num[r]]);
			cnts[num[r]]--;
			sum+=(cnts[num[r]]*cnts[num[r]]);
			r--;
		}
		while(l<Q[i].l)
		{
			sum-=(cnts[num[l]]*cnts[num[l]]);
			cnts[num[l]]--;
			sum+=(cnts[num[l]]*cnts[num[l]]);
			l++;
		}
		while(l>Q[i].l)
		{
			sum-=(cnts[num[l-1]]*cnts[num[l-1]]);
			cnts[num[l-1]]++;
			sum+=(cnts[num[l-1]]*cnts[num[l-1]]);
			l--;
		}
		if(Q[i].l==Q[i].r)
			ans[Q[i].id][0]=0,ans[Q[i].id][1]=1;
		else
		{
			long long a=sum-(Q[i].r-Q[i].l+1);
			long long b=(Q[i].r-Q[i].l+1)*(Q[i].r-Q[i].l);
			long long k=gcd(a,b);
			a/=k;b/=k;
			ans[Q[i].id][0]=a;ans[Q[i].id][1]=b;
		}
	}
}
void print()
{
	for(long long i=1;i<=m;i++)
		printf("%lld/%lld\n",ans[i][0],ans[i][1]);
}