#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const int MAXN=305;
const int MOD=1000000007;

int pow_mod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}

int n;
map<int,int> ni;
int fac[MAXN],inv[MAXN];
int C[MAXN][MAXN];
int dp[MAXN][MAXN];

int main()
{
	fac[0]=1;
	for(int i=1;i<MAXN;i++)
		fac[i]=(1LL*fac[i-1]*i)%MOD;
	inv[MAXN-1]=pow_mod(fac[MAXN-1],MOD-2);
	for(int i=MAXN-2;i>=1;i--)
		inv[i]=(1LL*inv[i+1]*(i+1))%MOD;
	
	C[0][0]=1;
	for(int i=1;i<MAXN;i++)
	{
		C[i][0]=1;
		for(int j=1;j<MAXN;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
	}
	
	scanf("%d",&n);
	for(int i=1,a;i<=n;i++)
	{
		scanf("%d",&a);
		for(int p=2;1LL*p*p<=a;p++)
			while(a%(p*p)==0)
				a/=p*p;
		ni[a]++;
	}
	
	dp[0][0]=1;
	map<int,int>::iterator it=ni.begin();
	int cnt=0;
	for(int i=1,num=it->second;it!=ni.end();it++,i++,num+=it->second,cnt++)
		for(int k=i;k<=num;k++)
			for(int j=1;j<=k&&j<=it->second;j++)
				dp[i][k]=(dp[i][k]+1LL*dp[i-1][k-j]*C[it->second-1][j-1]%MOD*fac[it->second]%MOD*inv[j]%MOD)%MOD;
	
	int ans=0;
	for(int k=n,flag=1;k>=1;k--,flag=-flag)
		ans=(ans+MOD+1LL*flag*dp[cnt][k]*fac[k]%MOD)%MOD;
	printf("%d\n",ans);
	
	return 0;
}
