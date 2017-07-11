#include<cstdio>
#include<cstring>
const int MAXD=13;
int dp[MAXD][MAXD][MAXD][2];
char num[MAXD];
int main()
{
	dp[0][0][0][0]=1;
	for(int i=1,bit=1;i<=10;i++,bit=(bit*10)%13)
		for(int j=0;j<10;j++)
			for(int r=0;r<13;r++)
				for(int k=0;k<10;k++)
				{
					dp[i][j][r][1]+=dp[i-1][k][(r-j*bit%13+13)%13][1];
					if(j==1&&k==3)
						dp[i][j][r][1]+=dp[i-1][k][(r-j*bit%13+13)%13][0];
					if(j!=1||k!=3)
						dp[i][j][r][0]+=dp[i-1][k][(r-j*bit%13+13)%13][0];
				}
	int len,ans;
	while(scanf("%s",num)!=EOF)
	{
		ans=0;
		len=strlen(num);
		int bit=1,rest=0;
		bool suc=0;
		for(int i=1;i<len;i++)bit*=10;
		for(int i=0;i<len;i++,bit/=10)
		{
			for(int j=0;j<num[i]-'0';j++)
			{
				if((j==3&&i>0&&num[i-1]=='1')||suc==1)
					ans+=dp[len-i][j][(26-rest)%13][0];
				ans+=dp[len-i][j][(26-rest)%13][1];
			}
			suc|=(num[i]=='3'&&num[i-1]=='1');
			rest=(rest+(num[i]-'0')*bit%13)%13;
		}
		ans+=dp[0][0][(26-rest)%13][!suc];
		printf("%d\n",ans);
	}
	return 0;
}
