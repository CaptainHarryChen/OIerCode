#include<cstdio>
#ifdef DEBUG
#include<ctime>
#endif
const int MAXN=3001,MAXN2=3000*3000+1,MOD=998244353;

inline int PowMod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*a*ret)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}

int fac[MAXN],ifac[MAXN],pow2[MAXN2],flag[MAXN];
int f[MAXN][MAXN],captain[MAXN][MAXN];

int main()
{
#ifdef DEBUG
	clock_t st=clock();
	freopen("in.txt","r",stdin);
#endif
	fac[0]=1;
	for(register int i=1;i<MAXN;i++)
		fac[i]=(1LL*fac[i-1]*i)%MOD;
	ifac[MAXN-1]=PowMod(fac[MAXN-1],MOD-2);
	for(register int i=MAXN-2;i>=0;i--)
		ifac[i]=(1LL*ifac[i+1]*(i+1))%MOD;
	
	pow2[0]=1;
	for(register int i=1;i<MAXN2;i++)
		pow2[i]=(pow2[i-1]<<1)%MOD;
		
	flag[0]=1;
	for(register int i=1;i<MAXN;i++)
		flag[i]=-flag[i-1];
		
	for(register int i=0;i<MAXN;i++)//n-u;m-v
	{
		f[i][i]=ifac[i];
		for(register int j=i-1;j>=0;j--)//x;y
			f[i][j]=(f[i][j+1]+1LL*flag[i-j]*ifac[j]%MOD*ifac[i-j])%MOD;
	}
	
	for(register int i=0;i<MAXN;i++)
		for(register int j=0;j<MAXN;j++)
			captain[i][j]=(1LL*pow2[i*j]*ifac[i]%MOD*ifac[j]%MOD);
	
	
	int n,m,x,y,ans,sum=0;
	while(scanf("%d%d%d%d",&n,&m,&x,&y)!=EOF)
	{
		ans=(1LL*fac[n]*fac[m])%MOD;
		sum=0;
		for(register int u=0;u<=n-x;u++)
			for(register int v=0;v<=m-y;v++)
				sum=(sum+1LL*captain[u][v]*f[n-u][x]%MOD*f[m-v][y]%MOD)%MOD;
		ans=(1LL*ans*sum%MOD+MOD)%MOD;
		printf("%d\n",ans);
	}
#ifdef DEBUG
	printf("%dms\n",(int)(clock()-st));
#endif
	return 0;
}
