#include<cstdio>
#include<cstring>
const int MAXK=1005,MOD=1000000007;

int pow_mod(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=(1LL*res*a)%MOD;
		b>>=1;
		a=(1LL*a*a)%MOD;
	}
	return res;
}
int inv(int x)
{return pow_mod(x,MOD-2);}

int dp[MAXK][MAXK];
int k,pa,pb;

int DP(int i,int j)
{
	if(i+j>=k)
		return (i+j+1LL*pa*inv(pb)%MOD)%MOD;
	if(dp[i][j]!=-1)
		return dp[i][j];
	return dp[i][j]=(1LL*((1LL*pa*DP(i+1,j))%MOD+(1LL*pb*DP(i,i+j))%MOD)*inv(pa+pb))%MOD;
}

int main()
{
	scanf("%d%d%d",&k,&pa,&pb);
	memset(dp,-1,sizeof dp);
	printf("%d\n",DP(1,0));
	return 0;
}
