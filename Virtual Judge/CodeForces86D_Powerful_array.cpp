#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXA=1000005;

int n,q,blksiz;
int a[MAXN];

struct query
{
	int l,r,id;
	long long ans;
	bool operator < (const query &t)const
	{return (l/blksiz)<(t.l/blksiz)||((l/blksiz)==(t.l/blksiz)&&r<t.r);}
}que[MAXN];

bool cmp(query a,query b)
{return a.id<b.id;}
int cnt[MAXA];

long long calc(int num,int i)
{return 1LL*num*num*i;}

int main()
{
	scanf("%d%d",&n,&q);
	blksiz=sqrt(n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&que[i].l,&que[i].r);
		que[i].id=i;
	}
	sort(que+1,que+q+1);
	int l=1,r=1;
	long long ans=a[1];
	cnt[a[1]]=1;
	for(int i=1;i<=q;i++)
	{
		while(r<que[i].r)
		{
			r++;
			ans-=calc(cnt[a[r]],a[r]);
			cnt[a[r]]++;
			ans+=calc(cnt[a[r]],a[r]);
		}
		while(l<que[i].l)
		{
			ans-=calc(cnt[a[l]],a[l]);
			cnt[a[l]]--;
			ans+=calc(cnt[a[l]],a[l]);
			l++;
		}
		while(r>que[i].r)
		{
			ans-=calc(cnt[a[r]],a[r]);
			cnt[a[r]]--;
			ans+=calc(cnt[a[r]],a[r]);
			r--;
		}
		while(l>que[i].l)
		{
			l--;
			ans-=calc(cnt[a[l]],a[l]);
			cnt[a[l]]++;
			ans+=calc(cnt[a[l]],a[l]);
		}
		que[i].ans=ans;
	}
	sort(que+1,que+q+1,cmp);
	for(int i=1;i<=q;i++)
		printf("%lld\n",que[i].ans);
	return 0;
}
