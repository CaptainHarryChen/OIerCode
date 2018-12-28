#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int N,A[MAXN],dp[MAXN],best;

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
		scanf("%d",&A[i]);
	sort(A+1,A+N+1);
	for(int i=1;i<=N;i++)
	{
		best=max(best,A[i]-dp[i-1]);
		dp[i]=best;
	}
	printf("%d\n",dp[N]);
	
	return 0;
}
