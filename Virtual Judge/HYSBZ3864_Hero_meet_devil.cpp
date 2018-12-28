#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1005,MAXL=20,MAXS=(1<<15)+10,MOD=1000000007;
const char ID[]="ACGT";

int T,n,m,dp[2][MAXS],tr[MAXS][4],ans[MAXN];
char str[MAXL];
int f[MAXL],g[MAXL];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%d",str+1,&m);
		n=strlen(str+1);
		for(int s=0;s<(1<<n);s++)
		{
			memset(f,0,sizeof f);
			memset(g,0,sizeof g);
			for(int j=1;j<=n;j++)
				f[j]=f[j-1]+((s>>(j-1))&1);
			for(int k=0;k<4;k++)
			{
				for(int j=1;j<=n;j++)
				{
					g[j]=max(g[j-1],f[j]);
					if(ID[k]==str[j])
						g[j]=max(g[j],f[j-1]+1);
				}
				tr[s][k]=0;
				for(int j=1;j<=n;j++)
					if(g[j]-g[j-1])
						tr[s][k]|=1<<(j-1);
			}
		}
		memset(dp,0,sizeof dp);
		dp[0][0]=1;
		for(int i=1;i<=m;i++)
		{
			int p=i&1;
			memset(dp[p],0,sizeof dp[p]);
			for(int s=0;s<(1<<n);s++)
				for(int k=0;k<4;k++)
					(dp[p][tr[s][k]]+=dp[p^1][s])%=MOD;
		}
		memset(ans,0,sizeof ans);
		for(int s=0;s<(1<<n);s++)
			(ans[__builtin_popcount(s)]+=dp[m&1][s])%=MOD;
		for(int i=0;i<=n;i++)
			printf("%d\n",ans[i]);
	}
	return 0;
}
