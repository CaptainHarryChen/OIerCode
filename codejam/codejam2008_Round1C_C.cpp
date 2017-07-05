#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 500005
typedef pair<long long,long long>Pos;
long long n,a[MAXN],tree[MAXN*4],A[MAXN];
long long GetSum(long long id,long long l,long long r,long long L,long long R)
{
	if(R<l||r<L)
		return 0;
	if(l<=L&&R<=r)
		return tree[id];
	long long sum=0;
	sum+=GetSum(id*2,l,r,L,(L+R)/2);
	sum+=GetSum(id*2+1,l,r,(L+R)/2+1,R);
	return sum;
}
void Insert(long long id,long long pos,long long val,long long L,long long R)
{
	if(R<pos||pos<L)
		return;
	if(L==pos&&R==pos)
	{
		tree[id]=(tree[id]+val)%1000000007;
		return;
	}
	Insert(id*2,pos,val,L,(L+R)/2);
	Insert(id*2+1,pos,val,(L+R)/2+1,R);
	tree[id]=(tree[id*2]+tree[id*2+1])%1000000007;
}
Pos b[MAXN];
long long cnt[MAXN];
int main()
{
	long long N,m,X,Y,Z;
	scanf("%I64d",&N);
	for(long long Case=1;Case<=N;Case++)
	{
		memset(tree,0,sizeof tree);
		scanf("%I64d%I64d%I64d%I64d%I64d",&n,&m,&X,&Y,&Z);
		for(long long i=0;i<m;i++)
			scanf("%I64d",A+i);
		for(long long i=0;i<n;i++)
		{
			a[i+1]=A[i%m];
			A[i%m]=(long long)((1LL * X * A[i % m] + 1LL * Y * (i + 1)) % Z);
		}
		for(long long i=1;i<=n;i++)
			b[i]=make_pair(a[i],i);
		sort(b+1,b+n+1);
		long long ans=0;
		for(long long i=1,j;i<=n;)
		{
			j=i;
			do
			{
				cnt[j]=GetSum(1,1,b[j].second-1,1,n)+1;
				ans=(ans+cnt[j])%1000000007;
				j++;
			}while(b[j].first==b[i].first&&j<=n);
			for(long long k=i;k<j;k++)
				Insert(1,b[k].second,cnt[k],1,n);
			i=j;
		}
		printf("Case #%I64d: %I64d\n",Case,ans);
	}
	return 0;
}
