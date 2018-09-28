#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=105;

int N,M,X,Y;
char mp[MAXN][MAXN];
short dp[MAXN][MAXN][MAXN][MAXN];
short sum[MAXN][MAXN];

short CountRect(int u,int l,int d,int r)
{
	return sum[d][r]-sum[d][l-1]-sum[u-1][r]+sum[u-1][l-1];
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++)
	{
		scanf("%s",mp[i]+1);
		for(int j=1;j<=M;j++)
			if(mp[i][j]=='E')
				X=i,Y=j;
	}
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(mp[i][j]=='o');
	int ans=0;
	for(int u=X;u>0;u--)
		for(int l=Y;l>0;l--)
			for(int d=X;d<=N;d++)
				for(int r=Y;r<=M;r++)
				{
					ans=max(ans,(int)dp[u][l][d][r]);
					//printf("dp[(%d,%d),(%d,%d)]=%d ",u,l,d,r,(int)dp[u][l][d][r]);
					int U=d-X+1,L=r-Y+1,D=N-(X-u),R=M-(Y-l);
					//printf("Area:(%d,%d),(%d,%d)\n",U,L,D,R);
					if(u>U)
						dp[u-1][l][d][r]=max((int)dp[u-1][l][d][r],dp[u][l][d][r]+CountRect(u-1,max(L,l),u-1,min(R,r)));
					if(l>L)
						dp[u][l-1][d][r]=max((int)dp[u][l-1][d][r],dp[u][l][d][r]+CountRect(max(U,u),l-1,min(D,d),l-1));
					if(d<D)
						dp[u][l][d+1][r]=max((int)dp[u][l][d+1][r],dp[u][l][d][r]+CountRect(d+1,max(L,l),d+1,min(R,r)));
					if(r<R)
						dp[u][l][d][r+1]=max((int)dp[u][l][d][r+1],dp[u][l][d][r]+CountRect(max(U,u),r+1,min(D,d),r+1));
				}
	printf("%d\n",ans);

    return 0;
}
