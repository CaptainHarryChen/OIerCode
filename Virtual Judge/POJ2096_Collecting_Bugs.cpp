#include<cstdio>
const int MAXN=1005;

int n,s;
double dp[MAXN][MAXN];

int main()
{
	scanf("%d%d",&n,&s);
		
	dp[n][s]=0;
	for(int i=n;i>=0;i--)
		for(int j=s;j>=0;j--)
		{
			if(i==n&&j==s)
				continue;
			double p1=1.0*i/n*j/s,p2=1.0*(n-i)/n*j/s,p3=1.0*i/n*(s-j)/s,p4=1.0*(n-i)/n*(s-j)/s;
			dp[i][j]=(dp[i+1][j]*p2+dp[i][j+1]*p3+dp[i+1][j+1]*p4+1)/(1-p1);
		}
			
	printf("%.4f\n",dp[0][0]);
	
	return 0;
}
