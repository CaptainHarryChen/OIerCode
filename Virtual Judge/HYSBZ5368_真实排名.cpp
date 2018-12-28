#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MOD=998244353;

int PowMod(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=1LL*res*a%MOD;
		a=1LL*a*a%MOD;
		b>>=1;
	}
	return res;
}

int n,k;
pair<int,int> A[MAXN];
int ans[MAXN];

int fac[MAXN],ifac[MAXN];
int C(int n,int r)
{
	if(n<r)
		return 0;
	return 1LL*fac[n]*ifac[n-r]%MOD*ifac[r]%MOD;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&A[i].first);
		A[i].second=i;
	}
	A[n+1].first=-1;
	sort(A+1,A+n+1);
	
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=1LL*fac[i-1]*i%MOD;
	ifac[n]=PowMod(fac[n],MOD-2);
	for(int i=n-1;i>=0;i--)
		ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;

	int last=1;
	for(int i=2;i<=n+1;i++)
		if(A[i].first!=A[i-1].first)
		{
			int pos,tmp=0;
			pos=lower_bound(A+1,A+n+1,make_pair((A[last].first+1)/2,0))-A;
			(tmp+=C(pos-1+n-last,k))%=MOD;
			pos=lower_bound(A+1,A+n+1,make_pair(A[last].first*2,0))-A;
			if(pos-last<=k)
				(tmp+=C(last-1+n-pos+1,k-(pos-last)))%=MOD;
			if(A[last].first==0)
				tmp=C(n,k);
			for(int j=last;j<i;j++)
				ans[A[j].second]=tmp;
			last=i;
		}
	
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	
	return 0;
}