#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=53,MOD=1000000007;

long long C[MAXN][MAXN];
long long dp[MAXN][MAXN*2];//有i个数，和为1+j*V的方案数

int main()
{
	int n=0;
	scanf("%d",&n);
	C[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=n;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
	int zero=n;
	dp[1][zero]=1;//2^0有一个
	dp[1][-1+zero]=1;//-2^0有一个
	for(int i=1;i<=n;i++)//有i个数
		for(int j=-i;j<=i;j++)//和为1+j*V（V不管是多少，反正为2的幂）
			if(dp[i][j+zero])
			{
				//printf("dp[%d][%d]=%lld\n",i,j,dp[i][j+zero]);
				for(int k=max(1,abs(j));k+i<=n;k++)//增加k个2*V
					for(int pos=0;pos<=k;pos++)//k个数中有pos个正数
					{
						int neg=k-pos;//neg个负数
						if((j+pos-neg)%2!=0)
							continue;
						int nsum=(j+pos-neg)/2;//新的和为1+nsum*2*V
						if(nsum<-n||nsum>n)
							continue;
						//i+k个中，选k个作为V值；k个中，选pos个正数
						(dp[i+k][nsum+zero]+=dp[i][j+zero]*C[i+k][k]%MOD*C[k][pos]%MOD)%=MOD;
					}
			}
	printf("%lld\n",dp[n][zero]);
			
	return 0;
}
