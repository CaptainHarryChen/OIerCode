#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXD=2500,MOD=1000000007;

int PowMod(int a,int b)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(1LL*ret*a)%MOD;
		a=(1LL*a*a)%MOD;
		b>>=1;
	}
	return ret;
}

int dp[MAXD];
vector<int> fac;

int main()
{
	int N,K,ans=0;
	scanf("%d%d",&N,&K);
	for(int i=1;1LL*i*i<=N;i++)
		if(N%i==0)
		{
			fac.push_back(i);
			if(1LL*i*i!=N)
				fac.push_back(N/i);
		}
	sort(fac.begin(),fac.end());
	for(int i=0;i<(int)fac.size();i++)
	{
		int d=fac[i];
		dp[i]=PowMod(K,(d+1)/2);
		for(int j=0;j<i;j++)
			if(d%fac[j]==0)
				dp[i]=(dp[i]-dp[j]+MOD)%MOD;
		if(d%2==0)
			d/=2;
		ans=(ans+(1LL*dp[i]*d)%MOD)%MOD;
	}
	
	printf("%d\n",ans);
	
	return 0;
}
