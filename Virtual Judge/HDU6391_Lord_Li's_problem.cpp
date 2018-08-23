#include<cstdio>
const int MAXN=43,MAXK=23,MOD=19260817;

int pow(int a,int b)
{
    int ret=1;
    while(b)
    {
        if(b&1)
            ret=(1LL*ret*a)%MOD;
        b>>=1;
        a=(1LL*a*a)%MOD;
    }
    return ret;
}
int fac[MAXN],ifac[MAXN];
void Init()
{
	fac[0]=1;
	for(int i=1;i<MAXN;i++)
		fac[i]=(1LL*fac[i-1]*i)%MOD;
	ifac[MAXN-1]=pow(fac[MAXN-1],MOD-2);
	for(int i=MAXN-2;i>=0;i--)
		ifac[i]=(1LL*ifac[i+1]*(i+1))%MOD;
}
int C(int n,int r)
{return 1LL*fac[n]*ifac[n-r]%MOD*ifac[r]%MOD;}

int dp[MAXK][MAXN];
char S[MAXN],T[MAXN];

int main()
{
	//freopen("wa.out","w",stdout);
	Init();
	int N,K;
	for(int test=1;;test++)
	{
		scanf("%d%d",&N,&K);
		if(N==0&&K==0)
			break;
		scanf("%s%s",S,T);
		dp[0][0]=1;
		for(int i=1;i<=K;i++)
			for(int j=0;j<=N;j++)
			{
				dp[i][j]=0;
				if(j>=3)
					(dp[i][j]+=1LL*dp[i-1][j-3]*C(N-(j-3),3)%MOD)%=MOD;
				if(j>=1)
					(dp[i][j]+=1LL*dp[i-1][j-1]*C(N-(j-1),2)%MOD*C(j-1,1)%MOD)%=MOD;
				if(j+1<=N)
					(dp[i][j]+=1LL*dp[i-1][j+1]*C(N-(j+1),1)%MOD*C(j+1,2)%MOD)%=MOD;
				if(j+3<=N)
					(dp[i][j]+=1LL*dp[i-1][j+3]*C(j+3,3)%MOD)%=MOD;
				if(i>=2)
					dp[i][j]=(dp[i][j]-1LL*dp[i-2][j]*(i-1)%MOD*(C(N,3)-(i-2))%MOD+MOD)%MOD;
			}
		int cnt=0;
		for(int i=0;i<N;i++)
			cnt+=(S[i]!=T[i]);
		int ans=1LL*dp[K][cnt]*pow(C(N,cnt),MOD-2)%MOD*ifac[K]%MOD;
		printf("Case #%d: %d\n",test,ans);
	}
	
	return 0;
}
