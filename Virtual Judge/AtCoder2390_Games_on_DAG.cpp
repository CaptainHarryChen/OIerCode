#include<cstdio>
const int MAXN=18,MAXS=(1<<15)+10,MOD=1000000007;

int N,M;
int G[MAXN];
int dp[MAXS],pw2[MAXN*MAXN];

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=M;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		v--;
		G[u]|=(1<<v);
	}
	
	dp[0]=1;
	pw2[0]=1;
	for(int i=1;i<=M;i++)
		pw2[i]=(pw2[i-1]<<1)%MOD;
	for(int S=1;S<(1<<N);S++)
		for(int U=S;U;U=(U-1)&S)
			if((U&1)==((U>>1)&1))
			{
				int T=S^U;
				int tmp=1;
				for(int i=1;i<=N;i++)
					if(S&(1<<(i-1)))
					{
						if(U&(1<<(i-1)))
							tmp=1LL*tmp*pw2[__builtin_popcount(G[i]&T)]%MOD;
						else
							tmp=1LL*tmp*(pw2[__builtin_popcount(G[i]&U)]-1)%MOD;
					}
				dp[S]=(dp[S]+1LL*dp[T]*tmp%MOD)%MOD;
			}
	int ans=(pw2[M]-dp[(1<<N)-1]+MOD)%MOD;
	printf("%d\n",ans);
	
	return 0;
}
