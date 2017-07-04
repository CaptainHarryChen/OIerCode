#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max(a,b) ((a)>(b)?(a):(b))
#define MAXN 105
int dp[MAXN][MAXN][MAXN];
int pos[MAXN];
int main()
{
	int T,n,m,i,j,k,l,x,ans,ct,mov;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		m/=2;
		ct=0;
		memset(dp,-1,sizeof dp);
		for(i=1;i<=n;i++)
		{
			scanf("%1d",&x);
			if(x==2)
				pos[++ct]=i;
		}
		dp[0][0][0]=0;
		for(i=1;i<=ct;i++)
			for(j=i,mov=abs(pos[i]-j);j<=n-ct+i;j++,mov=abs(pos[i]-j))
				for(k=mov;k<=m;k++)
				{
					for(l=i-1;l<=j-1;l++)
						if(~dp[i-1][l][k-mov])
							dp[i][j][k]=max(dp[i][j][k],dp[i-1][l][k-mov]+(j-l>2&&l!=0));
				}
		ans=0;
		if(ct!=0)
			for(j=ct,mov=abs(pos[ct]-j);j<=n;j++,mov=abs(pos[ct]-j))
				for(k=mov;k<=m;k++)
					ans=max(ans,dp[ct][j][k]+(j<=n-2));
		printf("%d\n",ans);
	}
	return 0;
}
