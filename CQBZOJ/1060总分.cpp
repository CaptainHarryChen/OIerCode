#include<iostream>
#define MAXN 10010
using namespace std;
int M,N,w[MAXN],v[MAXN],dp[MAXN];
int main()
{
	cin>>M>>N;
	for(int i=1;i<=N;i++)
		cin>>v[i]>>w[i];
	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			if(j>=w[i])
				dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
	int maxdp=0;
	for(int i=1;i<=M;i++)
		maxdp=max(maxdp,dp[i]);
	cout<<maxdp<<endl;
	return 0;
}
