#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int N,M;
int A[MAXN],cnt[MAXN];
int cov[MAXN];

int main()
{
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",&A[i]);
		cnt[A[i]]++;
	}
	int ans=N;
	for(int i=1;i<=N;i++)
		for(int j=i-cnt[i]+1;j<=i;j++)
		{
			if(cov[max(1,j)]==0)
				ans--;
			cov[max(1,j)]++;
		}
	for(int i=1;i<=M;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		cov[max(1,A[x]-cnt[A[x]]+1)]--;
		if(cov[max(1,A[x]-cnt[A[x]]+1)]==0)
			ans++;
		cnt[A[x]]--;
		A[x]=y;
		cnt[y]++;
		if(cov[max(1,y-cnt[y]+1)]==0)
			ans--;
		cov[max(1,y-cnt[y]+1)]++;
		printf("%d\n",ans);
	}
		
	
	return 0;
}
