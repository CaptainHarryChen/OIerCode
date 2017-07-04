#include<iostream>
#include<cstring>
using namespace std;
int K,N,num[205],dp[2000010],S;
int main()
{
	cin>>K>>N;
	for(int i=1;i<=N;i++)
	{
		cin>>num[i];
		S=max(S,num[i]);
	}
	memset(dp,127,sizeof dp);
	dp[0]=0;
	S*=K;
	for(int i=1;i<=S;i++)
	{
		for(int j=1;j<=N;j++)
			if(i>=num[j])
				dp[i]=min(dp[i],dp[i-num[j]]+1);
		if(dp[i]>K)
		{cout<<i-1<<endl;return 0;}
	}
	cout<<S<<endl;
	return 0;
}
