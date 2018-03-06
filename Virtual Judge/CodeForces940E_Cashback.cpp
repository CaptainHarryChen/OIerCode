#include<cstdio>
#include<set>
using namespace std;
const int MAXN=100005;

multiset<int> S;
int n,c,a[MAXN];
long long sum[MAXN],dp[MAXN];

int main()
{
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		sum[i]=sum[i-1]+a[i];
		dp[i]=sum[i];
	}
	for(int i=1;i<=c&&i<=n;i++)
		S.insert(a[i]);
	for(int i=c;i<=n;i++)
	{
		dp[i]=min(dp[i],dp[i-c]+sum[i]-sum[i-c]-*S.begin());
		dp[i]=min(dp[i],dp[i-1]+a[i]);
		S.insert(a[i+1]);
		S.erase(S.find(a[i-c+1]));
	}
	printf("%I64d\n",dp[n]);
	return 0;
}
