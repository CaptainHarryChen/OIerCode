#include<cstdio>
const int MOD=100000000,MAXN=15,MAXS=400;
int N,M;
int state[MAXS],scnt;
int farm[MAXN];
int dp[MAXN][MAXS];
void dfs(int i,int s)
{
	if(i<0)
	{
		state[scnt++]=s;
		return;
	}
	dfs(i-1,s);
	if(i==M-1||((s&(1<<(i+1)))==0))
		dfs(i-1,s+(1<<i));
}
int main()
{
	scanf("%d%d",&N,&M);
	dfs(M-1,0);
	for(int i=1;i<=N;i++)
		for(int j=1,x,bit=1;j<=M;j++,bit<<=1)
		{
			scanf("%d",&x);
			if(x)
				farm[i]+=bit;
		}
	dp[0][0]=1;
	for(int i=1;i<=N;i++)
		for(int j=0,s=state[j];j<scnt;j++,s=state[j])
		{
			if((s&farm[i])==s)
				for(int k=0,ts=state[k];k<scnt;k++,ts=state[k])
					if((ts&s)==0)
						dp[i][j]=(dp[i][j]+dp[i-1][k])%MOD;
		}
	int ans=0;
	for(int j=0;j<scnt;j++)
		ans=(ans+dp[N][j])%MOD;
	printf("%d\n",ans);
	return 0;
}
