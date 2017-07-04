#include<iostream>
#include<cstring>
using namespace std;
int N,K;
char s[25];
long long dp[25][25];
long long get_num(int x,int y)
{
	long long sum=0;
	for(int i=x;i<=y;i++)
		sum=sum*10+s[i]-'0';
	return sum;
}
int main()
{
	cin>>(s+1);
	N=strlen(s+1);
	long long sum=0;
	memset(dp,127,sizeof dp);
	for(int i=1;i<=N;i++)
	{
		sum=sum*10+s[i]-'0';
		dp[i][0]=sum;
	}
	cin>>K;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=K&&j<=i-1;j++)
			for(int k=i-1;k>=j;k--)
				dp[i][j]=min(dp[i][j],dp[k][j-1]+get_num(k+1,i));
	cout<<dp[N][K]<<endl;
	return 0;
}
