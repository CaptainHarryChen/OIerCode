#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 105
int N,M,v[MAXN][MAXN],dp[MAXN][MAXN],pf[MAXN],p;
bool path[MAXN][MAXN];
void print_ans(int x,int y)
{
	if(x<=0)return;
	if(path[x][y])
	{
		print_ans(x-1,y-1);
		pf[p++]=y;
	}
	else
		print_ans(x,y-1);
}
int main()
{
	cin>>N>>M;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			cin>>v[i][j];
	memset(dp,128,sizeof dp);
	for(int i=0;i<=M;i++)
		dp[0][i]=0;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M-N+i;j++)
		{
			if(dp[i-1][j-1]+v[i][j]<=dp[i][j-1])
				dp[i][j]=dp[i][j-1];
			else
			{
				dp[i][j]=dp[i-1][j-1]+v[i][j];
				path[i][j]=1;
			}
		}
	cout<<dp[N][M]<<endl;
	print_ans(N,M);
	for(int i=0;i<p-1;i++)
		cout<<pf[i]<<' ';
	cout<<pf[p-1]<<endl;
	return 0;
}
