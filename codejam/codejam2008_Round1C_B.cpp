#include<cstdio>
#include<cstdlib>
#include<cstring>
#define MAXL 42
#define MODP 210
long long dp[MAXL][MODP];
char num[MAXL];
int getnum(int x,int y)
{
	int res=0;
	for(int i=x;i<=y;i++)
		res=(res*10+num[i]-'0')%210;
	return res;
}
int main()
{
	int N,len;
	scanf("%d",&N);
	for(int Case=1;Case<=N;Case++)
	{
		scanf("%s",num+1);
		len=strlen(num+1);
		memset(dp,0,sizeof dp);
		for(int j=1;j<=len;j++)
			dp[j][getnum(1,j)]++;
		for(int j=1;j<=len;j++)
			for(int r=0;r<210;r++)
				for(int k=1;k<=j;k++)
				{
					int x=getnum(k,j);
					dp[j][r]+=dp[k-1][(r-x+210)%210]+dp[k-1][(r+x)%210];
				}
		long long ans=0;
		for(int r=0;r<210;r++)
			if(r%2==0||r%3==0||r%5==0||r%7==0)
				ans+=dp[len][r];
		printf("Case #%d: %I64d\n",Case,ans);
	}
	return 0;
}
