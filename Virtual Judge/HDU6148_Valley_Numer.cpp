#include<cstdio>
#include<cstring>
const int MAXL=101,MAXN=11;
const long long MOD=1000000007LL;
long long dp[MAXL][MAXN][2];
long long sum[MAXL];
char num[MAXL+10];
void init()
{
	for(int j=0;j<MAXN;j++)
		dp[0][j][0]=dp[0][j][1]=1;
	for(int i=1;i<MAXL;i++)
	{
		for(int j=0;j<MAXN;j++)
		{
			for(int k=0;k<MAXN-1;k++)
				if(k>j)
					dp[i][j][0]=(dp[i][j][0]+dp[i-1][k][1])%MOD;
				else
				{
					if(k==0&&j==10)
						dp[i][j][0]=(dp[i][j][0]+dp[i-1][10][0])%MOD;
					else
						dp[i][j][0]=(dp[i][j][0]+dp[i-1][k][0])%MOD;
				}
			for(int k=j;k<MAXN-1;k++)
				dp[i][j][1]=(dp[i][j][1]+dp[i-1][k][1])%MOD;
		}
	}
}
int main()
{
	init();
	int T,len,s;
	scanf("%d",&T);
	long long ans;
	bool flag;
	while(T--)
	{
		scanf("%s",num);
		len=strlen(num);
		flag=false;
		ans=0;
		s=1;
		for(int i=0;i<len;i++)
		{
			if(flag&&num[i-1]>num[i])
			{
				s=0;
				break;
			}
			if(flag)
				for(int j=(i==0)?10:num[i-1]-'0';j<num[i]-'0';j++)
				{
					ans+=dp[len-i-1][j][1];
					ans%=MOD;
				}
			else
			{
				for(int j=0;j<num[i]-'0';j++)
					if(j>((i==0)?10:(num[i-1]-'0')))
					{
						ans+=dp[len-i-1][j][1];
						ans%=MOD;
					}
					else
					{
						if(i==0&&j==0)
							ans+=dp[len-i-1][10][0];
						else
							ans+=dp[len-i-1][j][0];
						ans%=MOD;
					}
			}
			if(i>0&&num[i-1]<num[i])
				flag=true;
		}
		ans+=s;
		printf("%I64d\n",ans-1);
	}
	return 0;
}
