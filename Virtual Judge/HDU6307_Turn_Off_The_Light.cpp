#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005,MOD=1000000007;

bool sum0[MAXN],sum1[MAXN];
int cnt0[MAXN],cnt1[MAXN];

void solve(int n,int A[],int ans[])
{
	int l=n+1,r=0;
	for(int i=1;i<=n;i++)
		if(A[i])
		{
			
			l=min(l,i);
			r=max(r,i);
		}
	if(l>r)
	{
		fill(ans+1,ans+n+1,0);
		return;
	}
	for(int i=1;i<=n;i++)
	{
		sum0[i]=sum0[i-1]^A[i]^1;
		sum1[i]=sum1[i-1]^A[i];
		cnt0[i]=cnt0[i-1]+sum0[i];
		cnt1[i]=cnt1[i-1]+sum1[i];
	}
	fill(ans+1,ans+n+1,0x7F7F7F7F);
	for(int i=1;i<=r;i++)
	{
		if(i<=l)
		{
			if(i==r)
			{ans[i]=3;continue;}
			ans[i]=r-i;
			if(sum0[i-1])
				ans[i]+=2LL*(cnt0[r-1]-cnt0[i-1]);
			else
				ans[i]+=2LL*(r-i-(cnt0[r-1]-cnt0[i-1]));
			if(sum0[r]^sum0[i-1]^1)
				ans[i]--;
		}
		else
		{
			ans[i]=i-l+r-l;
			if(sum1[l-1])
				ans[i]+=2LL*(cnt1[i-1]-cnt1[l-1]);
			else
				ans[i]+=2LL*(i-l-(cnt1[i-1]-cnt1[l-1]));
			if(sum0[i-1]^sum1[i-1]^sum1[l-1])
				ans[i]+=2LL*(cnt0[r-1]-cnt0[i-1]);
			else
				ans[i]+=2LL*(r-i-(cnt0[r-1]-cnt0[i-1]));
			if(sum0[r]^sum0[i-1]^sum1[i-1]^sum1[l-1]^1)
				ans[i]--;
		}
	}
}

int n,A[MAXN];
int ans1[MAXN],ans2[MAXN];

int main()
{

	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%1d",&A[i]);
		solve(n,A,ans1);
		reverse(A+1,A+n+1);
		solve(n,A,ans2);
		int ans=0;
		for(int i=1;i<=n;i++)
			(ans+=1LL*i*min(ans1[i],ans2[n+1-i])%MOD)%=MOD;
		printf("%d\n",ans);
	}
	
	return 0;
}
