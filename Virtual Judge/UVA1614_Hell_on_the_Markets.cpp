#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int n;
pair<int,int> A[MAXN];
int ans[MAXN];

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		long long sum=0;
		for(int i=1;i<=n;i++)
		{
			A[i].second=i;
			scanf("%d",&A[i].first);
			sum+=A[i].first;
		}
		if(sum&1)
		{
			puts("No");
			continue;
		}
		sort(A+1,A+n+1);
		sum/=2;
		for(int i=n;i>=1;i--)
		{
			if(A[i].first<=sum)
			{
				ans[A[i].second]=-1;
				sum-=A[i].first;
			}
			else
				ans[A[i].second]=1;
		}
		puts("Yes");
		for(int i=1;i<=n;i++)
			printf("%d%c",ans[i]," \n"[i==n]);
	}
	return 0;
}
