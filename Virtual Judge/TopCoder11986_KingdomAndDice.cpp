#include<cstdio>
#include<vector>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=55;
const double EPS=1e-6;
	
int fcmp(double a,double b)
{
	if(fabs(a-b)<EPS)
		return 0;
	if(a<b)
		return -1;
	return 1;
}

int n,X,m,W;
int A[MAXN],B[MAXN];
int bag[MAXN];
bool dp[MAXN*MAXN][MAXN*MAXN];

void PutOne(int v1,int v2,int w1,int w2)
{
	for(int j=w1;j>=v1;j--)
		for(int k=w2;k>=v2;k--)
			dp[j][k]|=dp[j-v1][k-v2];
}
void PutComplete(int v2,int w1,int w2)
{
	for(int j=1;j<=w1;j++)
		for(int k=v2;k<=w2;k++)
			dp[j][k]|=dp[j-1][k-v2];
}

void DP(int w1,int w2)
{
	memset(dp,0,sizeof dp);
	dp[0][0]=true;
	for(int i=0,num;i<=n;i++)
	{
		int cnt=bag[i];
		if(bag[i]*i>w2)
			PutComplete(i,w1,w2);
		else
		{
			for(num=1;num<cnt&&num<=w1&&i*num<=w2;cnt-=num,num<<=1)
				PutOne(num,i*num,w1,w2);
			PutOne(cnt,i*cnt,w1,w2);
		}
	}
}

double solve()
{
	sort(B+1,B+n+1);
	
	double ans1,ans2;
	for(int i=1;i<=n;i++)
	{
		bag[i-1]=B[i]-B[i-1]-1;
		for(int j=1;j<=n;j++)
			bag[i-1]-=(A[j]&&B[i-1]<A[j]&&A[j]<B[i]);
		bag[i-1]=min(bag[i-1],n-m);
	}
	bag[0]=n-m;
	bag[n]=X-B[n];
	for(int j=1;j<=n;j++)
		bag[n]-=(A[j]&&B[n]<A[j]);
	bag[n]=min(bag[n],n-m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			W+=(A[i]&&A[i]>B[j]);
	
	DP(n-m,n*n/2-W);
	
	int best=max(n*n/2-W,0);
	while(best&&dp[n-m][best]==false)
		best--;
	ans1=1.0*(best+W)/(n*n);
	
	for(int i=1;i<n;i++)
	{
		bag[i]=B[n-i+1]-B[n-i]-1;
		for(int j=1;j<=n;j++)
			bag[i]-=(A[j]&&B[n-i]<A[j]&&A[j]<B[n-i+1]);
		bag[i]=min(bag[i],n-m);
	}
	bag[n]=n-m;
	bag[0]=X-B[n];
	for(int j=1;j<=n;j++)
		bag[0]-=(A[j]&&B[n]<A[j]);
	bag[0]=min(bag[0],n-m);
	W=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			W+=(A[i]&&A[i]<B[j]);
	
	DP(n-m,n*n/2-W);
	
	best=max(n*n/2-W,0);
	while(best&&dp[n-m][best]==false)
		best--;
	ans2=1.0*(n*n-best-W)/(n*n);
	if(best==0&&dp[n-m][best]==false)
		ans2=0;
	
	int d=fcmp(fabs(ans1-0.5),fabs(ans2-0.5));
	if(d==-1||(d==0&&fcmp(ans1,ans2)==-1))
		return ans1;
	return ans2;
}

class KingdomAndDice
{
public:
	double newFairness(std::vector<int> &vA, std::vector<int> &vB, int vX)
	{
		n=vA.size();
		for(int i=0;i<n;i++)
		{
			A[i+1]=vA[i];
			if(vA[i])
				m++;
		}
		for(int i=0;i<n;i++)
			B[i+1]=vB[i];
		X=vX;
		return solve();
	}
};
