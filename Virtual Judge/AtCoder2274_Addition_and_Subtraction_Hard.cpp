#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long long MAXN=300005;

long long N,T[MAXN];
long long q[MAXN],head,tail;
long long sum[MAXN],y[MAXN];
long long L[MAXN],R[MAXN],f[MAXN],g[MAXN],h[MAXN];

void DP(long long dp[],long long N)
{
	q[head=tail=1]=0;
	y[0]=0;
	for(long long i=1;i<=N;i++)
	{
		while(head<tail)
		{
			long long a=q[tail-1],b=q[tail];
			if((y[b]-y[a])<1LL*i*(b-a))
				tail--;
			else
				break;
		}
		long long j=q[tail];
		dp[i]=max(dp[i-1],dp[j]+(i-j)*(i-j-1)/2+(i-j)-sum[i]+sum[j]);
		y[i]=dp[i]+1LL*(i-1)*i/2+sum[i];
		while(head<tail)
		{
			long long a=q[tail-1],b=q[tail],c=i;
			if((y[b]-y[a])*(c-b)<1LL*(y[c]-y[b])*(b-a))
				tail--;
			else
				break;
		}
		q[++tail]=i;
	}
}

void CDQ(long long l,long long r,long long mode)
{
	if(l==r)
	{
		f[l]=max(f[l],L[l-1]+R[r+1]+1-T[l]);
		return;
	}
	long long mid=(l+r+mode)/2;
	CDQ(l,mid,mode);
	CDQ(mid+1,r,mode);
	
	q[head=tail=1]=l-1;
	g[l-1]=L[l-1];
	y[l-1]=g[l-1]+(l-1-1)*(l-1)/2+sum[l-1];
	for(long long i=l;i<=mid;i++)
	{
		g[i]=L[i];
		y[i]=g[i]+1LL*(i-1)*i/2+sum[i];
		while(head<tail)
		{
			long long a=q[tail-1],b=q[tail],c=i;
			if((y[b]-y[a])*(c-b)<1LL*(y[c]-y[b])*(b-a))
				tail--;
			else
				break;
		}
		q[++tail]=i;
	}
	
	for(long long i=mid+1;i<=r;i++)
	{
		while(head<tail)
		{
			long long a=q[tail-1],b=q[tail];
			if((y[b]-y[a])<1LL*i*(b-a))
				tail--;
			else
				break;
		}
		long long j=q[tail];
		g[i]=g[j]+(i-j)*(i-j-1)/2+(i-j)-sum[i]+sum[j]+R[i+1];
	}
	
	for(long long i=r-1;i>mid;i--)
		g[i]=max(g[i],g[i+1]);
	for(long long i=mid+1;i<=r;i++)
		f[i]=max(f[i],g[i]);
}

int main()
{
	scanf("%lld",&N);
	for(long long i=1;i<=N;i++)
		scanf("%lld",&T[i]);
	
	for(long long i=1;i<=N;i++)
		sum[i]=sum[i-1]+T[i];
	DP(L,N);
	reverse(T+1,T+N+1);
	for(long long i=1;i<=N;i++)
		sum[i]=sum[i-1]+T[i];
	DP(R,N);
	reverse(R+1,R+N+1);

	memset(h,0x80,sizeof h);
	
	for(long long i=1;i<=N;i++)
		swap(L[i],R[N-i+1]);
	
	memset(f,0x80,sizeof f);
	CDQ(1,N,-1);
	for(long long i=1;i<=N;i++)
		h[i]=max(h[i],f[N-i+1]);

	reverse(T+1,T+N+1);
	for(long long i=1;i<=N;i++)
		swap(L[i],R[N-i+1]);
	
	for(long long i=1;i<=N;i++)
		sum[i]=sum[i-1]+T[i];
	
	memset(f,0x80,sizeof f);
	CDQ(1,N,0);
	for(long long i=1;i<=N;i++)
		h[i]=max(h[i],f[i]);
	
	long long M,P,X;
	scanf("%lld",&M);
	while(M--)
	{
		scanf("%lld%lld",&P,&X);
		long long ans=max(L[P-1]+R[P+1],h[P]+T[P]-X);
		printf("%lld\n",ans);
	}
	
	return 0;
}
