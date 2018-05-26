#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int MAXN=500005;

int n,k,d;
int a[MAXN];
bool dp[MAXN];

int main()
{
	scanf("%d%d%d",&n,&k,&d);
	
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	sort(a+1,a+n+1);
	
	dp[0]=1;
	int l=0,r=0,cnt=1;
	for(int i=k;i<=n;i++)
	{
		while(r<i-k)
			r++,cnt+=dp[r];
		while(l<=r&&a[i]-a[l+1]>d)
			cnt-=dp[l],l++;
		if(cnt)
			dp[i]=true;
	}
	
	if(dp[n])
		puts("YES");
	else
		puts("NO");
	
	return 0;
}
