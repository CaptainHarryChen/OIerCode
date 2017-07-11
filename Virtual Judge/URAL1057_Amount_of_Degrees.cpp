#include<cstdio>
const int MAXD=35,MAXN=10;
int dp[MAXD][2][MAXD];
void Init_DP()
{
	dp[0][0][0]=1;
	for(int i=1;i<MAXD;i++)
		for(int j=0;j<2;j++)
			for(int k=j;k<=i;k++)
				for(int x=0;x<2;x++)
					dp[i][j][k]+=dp[i-1][x][k-j];
}
int solve(int N,int K,int B)
{
	int bit=1,len=1,cnt=0,ret=0;
	while(1LL*bit*B<=1LL*N)
		bit*=B,len++;
	for(int i=1;i<=len&&cnt<=K;i++)
	{
		for(int j=0;j<2&&j<N/bit;j++)
			ret+=dp[len-i+1][j][K-cnt];
		if(N/bit>=2)
			break;
		cnt+=N/bit;
		N%=bit;
		bit/=B;
	}
	ret+=dp[0][0][K-cnt];
	return ret;
}
int main()
{
	Init_DP();
	int X,Y,K,B,ans;
	scanf("%d%d%d%d",&X,&Y,&K,&B);
	ans=solve(Y,K,B);
	ans-=solve(X-1,K,B);
	printf("%d\n",ans);
	return 0;
}
