#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const long long MAXN=100005;

long long n;
long long A[MAXN];

int main()
{
	scanf("%I64d",&n);
	long long sum=0,ave,k,ans=0;
	for(long long i=1;i<=n;i++)
	{
		scanf("%I64d",A+i);
		sum+=A[i];
	}
	ave=sum/n;
	k=n-(sum-ave*n);
	sort(A+1,A+n+1);
	for(int i=1;i<=k;i++)
		ans+=abs(ave-A[i]);
	for(int i=k+1;i<=n;i++)
		ans+=abs(A[i]-ave-1);
	ans/=2;
	printf("%I64d\n",ans);
	
	return 0;
}
