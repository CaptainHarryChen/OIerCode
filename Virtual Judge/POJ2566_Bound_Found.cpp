#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int seq[MAXN];
pair<int,int>sum[MAXN];
void solve(int &L,int &R,int &S,int q,int n)
{
	int ans=0x7FFFFFFF;
	int l=0,r=1,s;
	while(r<=n&&ans>0)
	{
		s=sum[r].first-sum[l].first;
		if(abs(q-s)<ans)
		{
			L=sum[l].second;
			R=sum[r].second;
			S=s;
			ans=abs(q-s);
		}
		if(s<q)r++;
		if(s>q)l++;
		if(s==q)break;
		if(l==r)r++;
	}
	if(L>R)
		swap(L,R);
	L++;
}
int main()
{
	while(1)
	{
		int n,k;
		scanf("%d%d",&n,&k);
		if(!n&&!k)break;
		sum[0]=make_pair(0,0);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",seq+i);
			sum[i]=make_pair(sum[i-1].first+seq[i],i);
		}
		sort(sum,sum+n+1);
		for(int i=1;i<=k;i++)
		{
			int l,r,s,q;
			scanf("%d",&q);
			solve(l,r,s,q,n);
			printf("%d %d %d\n",s,l,r);
		}
	}
	return 0;
}
