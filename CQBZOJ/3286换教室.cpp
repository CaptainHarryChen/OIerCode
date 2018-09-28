#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2005,MAXV=305,MAXE=900005;

int n,m,v,e;
int dis[MAXV][MAXV];
int c[MAXN],d[MAXN];
double k[MAXN];
double dp[MAXN][MAXN][2];

int main()
{
	scanf("%d%d%d%d",&n,&m,&v,&e);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	c[0]=d[0]=0;
	for(int i=1;i<=n;i++)
		scanf("%lf",&k[i]);
	memset(dis,0x3F,sizeof dis);
	for(int i=1;i<=v;i++)
		dis[0][i]=dis[i][i]=0;
	for(int i=1;i<=e;i++)
	{
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		dis[a][b]=min(dis[a][b],w);
		dis[b][a]=min(dis[b][a],w);
	}
	
	for(int k=1;k<=v;k++)
		for(int i=1;i<=v;i++)
			for(int j=1;j<=v;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	//fprintf(stderr,"%d %d %d %d",dis[73][22],dis[73][58],dis[82][22],dis[82][58]);
	for(int i=n-1;i>=1;i--)
		for(int j=0;j<=m;j++)
		{
			dp[i][j][0]=dp[i+1][j][0]+dis[c[i]][c[i+1]];
			if(j>0)
				dp[i][j][0]=min(dp[i][j][0],dp[i+1][j-1][1]+dis[c[i]][d[i+1]]*k[i+1]+dis[c[i]][c[i+1]]*(1-k[i+1]));
			//fprintf(stderr,"dp[%d][%d][%d]=%f\n",i,j,0,dp[i][j][0]);
			dp[i][j][1]=dp[i+1][j][0]+dis[c[i]][c[i+1]]*(1-k[i])+dis[d[i]][c[i+1]]*k[i];
			if(j>0)
				dp[i][j][1]=min(dp[i][j][1],dp[i+1][j-1][1]+dis[c[i]][c[i+1]]*(1-k[i])*(1-k[i+1])+dis[c[i]][d[i+1]]*(1-k[i])*k[i+1]+dis[d[i]][c[i+1]]*k[i]*(1-k[i+1])+dis[d[i]][d[i+1]]*k[i]*k[i+1]);
			//fprintf(stderr,"dp[%d][%d][%d]=%f\n",i,j,1,dp[i][j][1]);
		}
	double ans=1e100;
	for(int j=0;j<=m;j++)
		ans=min(ans,min(dp[1][j][0],m>j?dp[1][j][1]:1e100));
	printf("%.2f\n",ans);
	
	return 0;
}
