#include<cstdio>
#include<algorithm>
using namespace std;
const long long MOD=1000000007,MAXN=65;
long long dp[MAXN][MAXN][MAXN][MAXN];
long long arr[MAXN];
long long fac(long long x)
{
	long long ret=1;
	while(x)
	{
		ret=(ret*x)%MOD;
		x--;
	}
	return ret;
}
int main()
{
	long long n,c;
	scanf("%lld",&n);
	for(long long i=1;i<=n;i++)
		scanf("%lld",arr+i);
	sort(arr+1,arr+n+1);
	for(c=1;c<=n&&arr[c]==arr[1];c++);
	if(c>n)
	{
		printf("%lld\n",fac(n));
		return 0;
	}
	long long ans=fac(c-1);
	dp[c-1][0][0][c-1]=1;
	for(long long i=c-1;i<n;i++)
		for(long long l=c-1;l<i||l==c-1;l++)
			for(long long j=0;j<i;j++,j=max(j,c-1))
				for(long long k=0;k<l;k++,k=max(k,c-1))
				{
					if(arr[i+1]+arr[j]>=2*arr[i]||j==0)
					{
						dp[i+1][i][k][l]+=dp[i][j][k][l];
						dp[i+1][i][k][l]%=MOD;
					}
					if(arr[k]+arr[i+1]>=2*arr[l]||k==0)
					{
						dp[i+1][l][j][i]+=dp[i][j][k][l];
						dp[i+1][l][j][i]%=MOD;
					}
				}
	long long sum=0;
	for(long long l=c-1;l<n;l++)
		for(long long j=0;j<n;j++)
			for(long long k=0;k<l;k++)
			{
				sum+=dp[n][j][k][l];
				sum%=MOD;
			}
	ans=int((1LL*ans*sum)%MOD);
	printf("%lld\n",ans);
	return 0;
}
