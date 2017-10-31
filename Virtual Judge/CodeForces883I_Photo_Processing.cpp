#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005;
int v[MAXN];
int dp[MAXN];
bool check(int n,int k,int lim)
{
	for(int i=k;i<=n;i++)
	{
		dp[i]=dp[i-1];
		if(v[i]-v[dp[i-k]+1]<=lim)
			dp[i]=i;
	}
	return dp[n]==n;
}
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	if(k==1)
	{puts("0");return 0;}
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	sort(v+1,v+n+1);
	int L=0,R=v[n]-v[1];
	while(L<R)
	{
		int mid=(L+R)/2;
		if(check(n,k,mid))
			R=mid;
		else
			L=mid+1;
	}
	printf("%d\n",L);
	return 0;
}
