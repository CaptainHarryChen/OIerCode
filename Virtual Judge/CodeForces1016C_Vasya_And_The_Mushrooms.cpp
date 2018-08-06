#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005;

int n;
long long A[2][MAXN];
long long sum[2][MAXN],f[2][MAXN],g[2][MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=0;i<2;i++)
		for(int j=1;j<=n;j++)
			scanf("%I64d",&A[i][j]);
	for(int i=n;i>0;i--)
	{
		sum[0][i]=sum[0][i+1]+A[0][i];
		sum[1][i]=sum[1][i+1]+A[1][i];
	}
	for(int i=n;i>0;i--)
	{
		f[0][i]=f[0][i+1]+sum[0][i+1]+A[0][i];
		f[1][i]=f[1][i+1]+sum[1][i+1]+A[1][i];
	}
	for(int i=n;i>0;i--)
	{
		g[0][i]=g[0][i+1]+A[0][i]*(n-i+1);
		g[1][i]=g[1][i+1]+A[1][i]*(n-i+1);
	}
	
	long long tmp=0,ans=0,ti=0;
	int flag=0;
	for(int i=1;i<=n;)
	{
		ans=max(ans,tmp+f[flag][i]+sum[flag][i]*ti+g[flag^1][i]+sum[flag^1][i]*(ti+n-i+1));
		ti++;
		tmp+=A[flag][i]*ti;
		ti++;
		tmp+=A[flag^1][i]*ti;
		i++;flag^=1;
	}
	printf("%I64d\n",ans-sum[0][1]-sum[1][1]);
	
	return 0;
}
