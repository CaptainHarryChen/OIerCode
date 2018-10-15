#include<cstdio>
#include<cstring>
const int MAXN=10005,MOD=998244353;

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

int N;
char A[MAXN],B[MAXN];
int dp[MAXN][MAXN];

int fac[MAXN],ifac[MAXN];
int C(int n,int r)
{return 1LL*fac[n]*ifac[n-r]%MOD*ifac[r]%MOD;}

int main()
{
	scanf("%s%s",A+1,B+1);
	N=strlen(A+1);
	int X=0,Y=0;
	for(int i=1;i<=N;i++)
	{
		if(A[i]=='1'&&B[i]=='1')
			X++;
		else if(A[i]=='1')
			Y++;
	}
	
	fac[0]=1;
	for(int i=1;i<=N;i++)
		fac[i]=1LL*fac[i-1]*i%MOD;
	ifac[N]=PowMod(fac[N],MOD-2);
	for(int i=N-1;i>=0;i--)
		ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;
	
	for(int j=0;j<=Y;j++)
		dp[0][j]=1LL*fac[j]*fac[j]%MOD;
	for(int i=1;i<=X;i++)
		for(int j=1;j<=Y;j++)
			dp[i][j]=(1LL*dp[i-1][j]*i%MOD*j%MOD+1LL*dp[i][j-1]*j%MOD*j%MOD)%MOD;
	int ans=0;
	for(int i=0;i<=X;i++)
		ans=(ans+1LL*dp[X-i][Y]*fac[i]%MOD*fac[i]%MOD*C(X,i)%MOD*C(X+Y,i)%MOD)%MOD;
	printf("%d\n",ans);
	
	return 0;
}
