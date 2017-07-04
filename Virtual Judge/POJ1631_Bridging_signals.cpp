#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 40005
int a[MAXN],dp[MAXN];
int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d",a+i);
		memset(dp,0x7F,sizeof dp);
		for(int i=1;i<=n;i++)
			lower_bound(dp+1,dp+n+1,a[i])[0]=a[i];
		printf("%d\n",lower_bound(dp+1,dp+n+1,0x7F7F7F7F)-dp-1);
	}
	return 0;
}
