#include<cstdio>
const int MAXN=43,MAXS=(1<<18)+3,MOD=1000000007;

int N,X,Y,Z;
int dp[MAXN][MAXS];
int pow10[MAXN];

int main()
{
	scanf("%d%d%d%d",&N,&X,&Y,&Z);
	pow10[0]=1;
	for(int i=1;i<=N;i++)
		pow10[i]=(pow10[i-1]*10ll)%MOD;
	int ans=0;
	dp[0][1]=1;
	for(int i=0;i<=N;i++)
		for(int s=1;s<(1<<18);s++)
			if(dp[i][s])
			{
				/*printf("dp[%d][",i);
				for(int k=0;k<=17;k++)
					if(s&(1<<k))
						printf("%d ",k);
				printf("]=%d\n",dp[i][s]);*/
				
				
				if((s&(1<<Z))&&(s&(1<<(Y+Z)))&&(s&(1<<(X+Y+Z))))
				{
					(ans+=1LL*dp[i][s]*pow10[N-i]%MOD)%=MOD;
					continue;
				}
				for(int k=1;k<=10;k++)
					(dp[i+1][((s<<k)|1)&((1<<18)-1)]+=dp[i][s])%=MOD;
			}
		
	printf("%d\n",ans);
	
	return 0;
}
