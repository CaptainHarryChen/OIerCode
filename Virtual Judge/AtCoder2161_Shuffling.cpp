#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=3005,MOD=1000000007;

int PowMod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*a*ret)%MOD;
		b>>=1;
		a=(1LL*a*a)%MOD;
	}
	return ret;
}

int N,M;
int fac[MAXN],ifac[MAXN];
int sum[MAXN],A[MAXN],l[MAXN],r[MAXN],len[MAXN],cnt1[MAXN];
pair<int,int> seg[MAXN];
int dp[MAXN][MAXN];

int F(int a,int b)
{
	if(a<b)
		return 0;
	return 1LL*fac[a]*ifac[b]%MOD*ifac[a-b]%MOD;
}

int main()
{
	scanf("%d%d",&N,&M);
	
	fac[0]=1;
	for(int i=1;i<=N;i++)
		fac[i]=(1LL*fac[i-1]*i)%MOD;
	ifac[N]=PowMod(fac[N],MOD-2);
	for(int i=N-1;i>=0;i--)
		ifac[i]=(1LL*ifac[i+1]*(i+1))%MOD;
	
	for(int i=1;i<=N;i++)
	{
		scanf("%1d",&A[i]);
		sum[i]=sum[i-1]+A[i];
	}
	for(int i=1;i<=M;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
		seg[i]=make_pair(l[i],r[i]);
	}
	sort(seg+1,seg+M+1);
	int tmp=0;
	for(int i=2;i<=M+1;i++)
		if(seg[i].first!=seg[i-1].first&&seg[i-1].second>r[tmp])
		{
			l[++tmp]=seg[i-1].first;
			r[tmp]=seg[i-1].second;
		}
	M=tmp;
	for(int i=1;i<=M;i++)
	{
		len[i]=r[i]-l[i]+1;
		cnt1[i]=sum[r[i]]-sum[l[i]-1];
	}
	M++;
	l[M]=r[M]=N+1;
	len[M]=1;cnt1[M]=0;
	
	dp[1][sum[r[1]]-sum[l[1]-1]]=1;
	for(int i=2;i<=M;i++)
	{
		if(l[i]>r[i-1])
			for(int j=0;j<=len[i-1];j++)
				(dp[i][cnt1[i]]+=(1LL*dp[i-1][j]*F(len[i-1],j)%MOD))%=MOD;
		else
			for(int j=0;j<=r[i-1]-l[i]+1;j++)
				for(int k=j;k<=len[i-1];k++)
					(dp[i][j+sum[r[i]]-sum[r[i-1]]]+=(1LL*dp[i-1][k]*F(l[i]-l[i-1],k-j)%MOD))%=MOD;
	}
	
	printf("%d\n",dp[M][0]);
	
	return 0;
}
