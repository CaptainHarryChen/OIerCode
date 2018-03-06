#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=30005,MAXQ=200005,MAXA=1000005;

int n,q,blksiz;
int a[MAXN];

struct query
{
	int l,r,ans,id;
	bool operator < (const query &t)const
	{return (l/blksiz)<(t.l/blksiz)||((l/blksiz)==(t.l/blksiz)&&r<t.r);}
}que[MAXQ];

bool cmp(query a,query b)
{return a.id<b.id;}
int cnt[MAXA];

int main()
{
	scanf("%d",&n);
	blksiz=sqrt(n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&que[i].l,&que[i].r);
		que[i].id=i;
	}
	sort(que+1,que+q+1);
	int l=1,r=1,ans=1;
	cnt[a[1]]=1;
	for(int i=1;i<=q;i++)
	{
		while(r<que[i].r)
			r++,cnt[a[r]]++,ans+=(cnt[a[r]]==1);
		while(l<que[i].l)
			cnt[a[l]]--,ans-=(cnt[a[l]]==0),l++;
		while(r>que[i].r)
			cnt[a[r]]--,ans-=(cnt[a[r]]==0),r--;
		while(l>que[i].l)
			l--,cnt[a[l]]++,ans+=(cnt[a[l]]==1);
		que[i].ans=ans;
	}
	sort(que+1,que+q+1,cmp);
	for(int i=1;i<=q;i++)
		printf("%d\n",que[i].ans);
	return 0;
}
