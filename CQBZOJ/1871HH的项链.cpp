#include<cstdio>
#include<cmath>
#include<algorithm>
#define MAXN 50005
using namespace std;
int n,m,num[50005];
int pos[50005],cnts[1000005],ans[200005];
struct Quary
{
	int l,r,id;
	bool operator<(Quary b)const
	{return pos[l]<pos[b.l]||(pos[l]==pos[b.l]&&r<b.r);}
}Q[200005];
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
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&num[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&Q[i].l,&Q[i].r);
		Q[i].id=i;
	}
	int block=sqrt(n);
	for(int i=1;i<=n;i++)
		pos[i]=(i-1)/block+1;
	sort(Q+1,Q+m+1);
}
void solve()
{
	int sum=0;
	for(int i=1,l=1,r=0;i<=m;i++)
	{
		while(r<Q[i].r)
        {
            cnts[num[r+1]]++;
            sum+=(cnts[num[r+1]]==1);
            r++;
        }
        while(r>Q[i].r)
        {
            cnts[num[r]]--;
            sum-=(cnts[num[r]]==0);
            r--;
        }
        while(l<Q[i].l)
        {
            cnts[num[l]]--;
            sum-=(cnts[num[l]]==0);
            l++;
        }
        while(l>Q[i].l)
        {
            cnts[num[l-1]]++;
            sum+=(cnts[num[l-1]]==1);
            l--;
        }
		ans[Q[i].id]=sum;
	}
}
void print()
{
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
}
