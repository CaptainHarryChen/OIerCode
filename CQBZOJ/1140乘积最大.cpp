#include<iostream>
#include<cstring>
using namespace std;
int N,K;
long long dp[45][10];
char s[45];
long long get_num(int x,int y)
{
	if(y-x+1>18)
		return -1;
	long long sum=0;
	for(int i=x;i<=y;i++)
		sum=sum*10+s[i]-'0';
	return sum;
}
int main()
{
	cin>>N>>K;
	long long sum=0;
	for(int i=1;i<=N;i++)
	{
		cin>>s[i];
		sum=sum*10+s[i]-'0';
		dp[i][0]=sum;
	}
	for(int i=1;i<=N;i++)
		for(int j=1;j<=i-1&&j<=K;j++)
			for(int k=i-1;k>=j;k--)
				dp[i][j]=max(dp[i][j],dp[k][j-1]*get_num(k+1,i));
	cout<<dp[N][K]<<endl;
	return 0;
}
