#include<cstdio>
#include<cstring>
int dp[10][10];
int main()
{
	while(1)
	{
		int n,m,digit[10];
		scanf("%d%d",&m,&n);
		if(!m||!n)break;
		n++;
		memset(dp,0,sizeof dp);
		dp[0][0]=1;
		for(int i=1;i<=6;i++)
			for(int j=0;j<10;j++)
			{
				if(j==4)continue;
				for(int k=0;k<10;k++)
				{
					if(k==2&&j==6)continue;
					dp[i][j]+=dp[i-1][k];
				}
			}
		int ans=0,l;
		for(l=0;n;n/=10)
			digit[++l]=n%10;
		digit[l+1]=0;
		for(int i=l;i>0;i--)
		{
			for(int j=0;j<digit[i];j++)
				if(j!=4&&!(j==2&&digit[i+1]==6))
					ans+=dp[i][j];
			if(digit[i]==4||(digit[i]==2&&digit[i+1]==6))break;
		}
		for(l=0;m;m/=10)
			digit[++l]=m%10;
		digit[l+1]=0;
		for(int i=l;i>0;i--)
		{
			for(int j=0;j<digit[i];j++)
				if(j!=4&&!(j==2&&digit[i+1]==6))
					ans-=dp[i][j];
			if(digit[i]==4||(digit[i]==2&&digit[i+1]==6))break;
		}
		printf("%d\n",ans);
	}
	return 0;
}
