#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const long long MAXN=50005;

long long n,q,blksiz;
long long a[MAXN];

struct query
{
	long long l,r,ans1,ans2,id;
	bool operator < (const query &t)const
	{return (l/blksiz)<(t.l/blksiz)||((l/blksiz)==(t.l/blksiz)&&r<t.r);}
}que[MAXN];

bool cmp(query a,query b)
{return a.id<b.id;}
long long cnt[MAXN];

long long calc(long long num)
{
	if(num<=1)
		return 0;
	return num*(num-1)/2;
}

long long gcd(long long a,long long b)
{return b==0?a:gcd(b,a%b);}

int main()
{
	scanf("%lld%lld",&n,&q);
	blksiz=sqrt(n);
	for(long long i=1;i<=n;i++)
		scanf("%lld",a+i);
	for(long long i=1;i<=q;i++)
	{
		scanf("%lld%lld",&que[i].l,&que[i].r);
		que[i].id=i;
	}
	sort(que+1,que+q+1);
	long long l=1,r=1,ans=0;
	cnt[a[1]]=1;
	for(long long i=1;i<=q;i++)
	{
		while(r<que[i].r)
		{
			r++;
			ans-=calc(cnt[a[r]]);
			cnt[a[r]]++;
			ans+=calc(cnt[a[r]]);
		}
		while(l<que[i].l)
		{
			ans-=calc(cnt[a[l]]);
			cnt[a[l]]--;
			ans+=calc(cnt[a[l]]);
			l++;
		}
		while(r>que[i].r)
		{
			ans-=calc(cnt[a[r]]);
			cnt[a[r]]--;
			ans+=calc(cnt[a[r]]);
			r--;
		}
		while(l>que[i].l)
		{
			l--;
			ans-=calc(cnt[a[l]]);
			cnt[a[l]]++;
			ans+=calc(cnt[a[l]]);
		}
		if(ans==0)
			que[i].ans1=0,que[i].ans2=1;
		else
		{
			long long tot=(r-l+1)*(r-l)/2;
			long long g=gcd(ans,tot);
			que[i].ans1=ans/g;
			que[i].ans2=tot/g;
		}
	}
	sort(que+1,que+q+1,cmp);
	for(long long i=1;i<=q;i++)
		printf("%lld/%lld\n",que[i].ans1,que[i].ans2);
	return 0;
}
