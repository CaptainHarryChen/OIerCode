#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

class KingdomAndPassword
{
	static const long long MAXN=20,MAXS=(1<<16)+10;
	static const long long LLF=0x7FFFFFFFFFFFFFFFLL;
	
	long long n;
	long long old[MAXN],lim[MAXN];
	long long dp[MAXS][3],oldpas;
	
	long long DP0(long long S,long long len)// =
	{
		if(S==0)
			return 0;
		if(dp[S][0]!=-1)
			return dp[S][0];
		long long x=old[len],nS=-1;
		for(long long i=1;i<=n;i++)
			if(old[i]==x&&((S>>(i-1))&1))
			{
				nS=S^(1<<(i-1));
				break;
			}
		long long d0=DP0(nS,len-1);
		if(lim[len]==x||nS==-1||d0==-2)
		{
			dp[S][0]=-2;
			return -2;
		}
		dp[S][0]=d0*10LL+x;
		return dp[S][0];
	}
	long long DP1(long long S,long long len)// <
	{
		if(S==0)
			return -2;
		if(dp[S][1]!=-1)
			return dp[S][1];
		long long best=-1;
		for(long long i=1,x;i<=n;i++)
			if((S>>(i-1))&1)
			{
				x=old[i];
				if(lim[len]==x)
					continue;
				long long nS=S^(1<<(i-1));
				long long d0=DP0(nS,len-1),d1=DP1(nS,len-1);
				if(x<old[len]&&d0!=-2)
					best=max(best,d0*10LL+x);
				if(d1!=-2)
					best=max(best,d1*10LL+x);
			}
		if(best==-1)
		{
			dp[S][1]=-2;
			return -2;
		}
		dp[S][1]=best;
		return dp[S][1];
	}
	long long DP2(long long S,long long len)// >
	{
		if(S==0)
			return -2;
		if(dp[S][2]!=-1)
			return dp[S][2];
		long long best=LLF;
		for(long long i=1,x;i<=n;i++)
			if((S>>(i-1))&1)
			{
				x=old[i];
				if(lim[len]==x)
					continue;
				long long nS=S^(1<<(i-1));
				long long d0=DP0(nS,len-1),d2=DP2(nS,len-1);
				if(x>old[len]&&d0!=-2)
					best=min(best,d0*10LL+x);
				if(d2!=-2)
					best=min(best,d2*10LL+x);
			}
		if(best==LLF)
		{
			dp[S][2]=-2;
			return -2;
		}
		dp[S][2]=best;
		return dp[S][2];
	}
	long long solve()
	{
		memset(dp,-1,sizeof dp);
		long long S=(1<<n)-1;
		if(DP0(S,n)!=-2)// =
			return oldpas;
		long long res1=DP1(S,n);// >
		long long res2=DP2(S,n);// <
		if(res1==-2&&res2==-2)
			return -1;
		if(res1!=-2&&(res2==-2||oldpas-res1<=res2-oldpas))
			return res1;
		return res2;
	}
	
public:
	long long newPassword(long long _old,vector<int> &_lim)
	{
		n=0;oldpas=_old;
		while(_old)
		{
			old[++n]=_old%10LL;
			_old/=10LL;
		}
		for(long long i=1,j=n;i<j;i++,j--)
			swap(old[i],old[j]);
		for(long long i=0;i<n;i++)
			lim[i+1]=_lim[i];
		return solve();
	}
};
