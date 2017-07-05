#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 1005
int cnt[MAXN];
int pl[MAXN];
int main()
{
	int N,P,K,L,cur;
	long long ans;
	scanf("%d",&N);
	for(int Case=1;Case<=N;Case++)
	{
		scanf("%d%d%d",&P,&K,&L);
		for(int i=1;i<=K;i++)
			pl[i]=P;
		cur=1;
		for(int i=1;i<=L;i++)
			scanf("%d",cnt+i);
		sort(cnt+1,cnt+L+1);
		ans=0;
		for(int i=L;i>0;i--)
		{
			pl[cur]--;
			ans+=1LL*(P-pl[cur])*cnt[i];
			cur++;
			if(cur>K)cur-=K;
		}
		printf("Case #%d: %I64d\n",Case,ans);
	}
	return 0;
}
