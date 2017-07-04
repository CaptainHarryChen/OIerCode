#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 205
#define MAXR 1005
#define MAXM 10005
int N,M,R;
int S[MAXN][MAXN],L[MAXN][MAXN];
int task[MAXR];
int dp[MAXR][MAXN];
int main()
{
	while(1)
	{
		scanf("%d%d",&N,&M);
		if(!N&&!M)break;
		for(int i=1;i<=N;i++)
			for(int j=1;j<=N;j++)
				S[i][j]=L[i][j]=1000000;
		for(int i=1;i<=N;i++)
			S[i][i]=L[i][i]=0;
		for(int i=1;i<=M;i++)
		{
			int a,b,t;char s[3];
			scanf("%d%d%d%s",&a,&b,&t,s);
			if(s[0]=='S')
			{
				S[a][b]=min(S[a][b],t);
				S[b][a]=min(S[b][a],t);
			}
			else
			{
				L[a][b]=min(L[a][b],t);
				L[b][a]=min(L[b][a],t);
			}
		}
		for(int k=1;k<=N;k++)
			for(int i=1;i<=N;i++)
				for(int j=1;j<=N;j++)
				{
					S[i][j]=min(S[i][j],S[i][k]+S[k][j]);
					L[i][j]=min(L[i][j],L[i][k]+L[k][j]);
				}
		scanf("%d",&R);
		for(int i=1;i<=R;i++)
			scanf("%d",task+i);
		for(int i=1;i<=R;i++)
			for(int j=1;j<=N;j++)
				dp[i][j]=1000000;
		dp[1][task[1]]=0;
		for(int i=2;i<=R;i++)//the Captain position
			for(int j=1;j<=N;j++)//the Ship position
			{
				dp[i][j]=min(dp[i][j],dp[i-1][j]+L[task[i-1]][task[i]]);
				for(int k=1;k<=N;k++)
					dp[i][k]=min(dp[i][k],dp[i-1][j]+L[task[i-1]][j]+S[j][k]+L[k][task[i]]);
			}
		int ans=0x7FFFFFFF;
		for(int i=1;i<=N;i++)
			ans=min(ans,dp[R][i]);
		printf("%d\n",ans);
	}
	return 0;
}
