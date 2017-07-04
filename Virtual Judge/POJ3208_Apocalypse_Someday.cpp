#include<cstdio>
long long dp[30][10][10][2];
void init()
{
	for(int j=0;j<10;j++)
		dp[1][j][0][0]=1;
	for(int j=0;j<10;j++)
		for(int k=0;k<10;k++)
			dp[2][j][k][0]=1;
	for(int i=2;i<=12;i++)
		for(int j=0;j<10;j++)
			for(int k=0;k<10;k++)
				for(int n=0;n<10;n++)
				{
					dp[i+1][n][j][0]+=dp[i][j][k][0];
					if(j==6&&k==6&&n==6)
						dp[i+1][n][j][1]+=dp[i][j][k][0];
					else
						dp[i+1][n][j][1]+=dp[i][j][k][1];
				}
}
int getr(long long x)
{
	if(x==3666418)
	{x--;x++;}
	x++;
	int digit[25]={0},len,ret=0;
	for(len=0;x;x/=10LL)digit[++len]=x%10LL;
	if(len<3)return 0;
	for(int i=len;i>0;i--)
	{
		if(digit[i+1]==6&&digit[i+2]==6&&digit[i+3]==6)
		{
			int s=0;
			while(i)s=s*10+digit[i],i--;
			ret+=s;
			break;
		}
		for(int j=0;j<digit[i];j++)
		{
			if(digit[i+2]==6&&digit[i+1]==6&&j==6)
				for(int k=0;k<10;k++)
					ret+=dp[i][j][k][0];
			else
				for(int k=0;k<10;k++)
				{
					if(digit[i+1]==6&&j==6&&k==6)
						ret+=dp[i][j][k][0];
					else
						ret+=dp[i][j][k][1];
				}
		}
	}
	return ret;
}
int main()
{
	init();
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		long long l=666,r=9999999666LL,mid,ran;
		while(l<r)
		{
			mid=(l+r)>>1;
			ran=getr(mid);
			if(ran>=n)
				r=mid;
			else
				l=mid+1;
		}
		printf("%I64d\n",l);
	}
	return 0;
}
