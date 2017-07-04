#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 100005
pair<int,int>cow[MAXN];
int N;
bool cmp(pair<int,int> a,pair<int,int> b)
{return a.first*b.second<a.second*b.first;}
int main()
{
	scanf("%d",&N);
	long long sum=0,ans=0;
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d",&cow[i].first,&cow[i].second);
		sum+=1LL*cow[i].second;
	}
	sort(cow+1,cow+N+1,cmp);
	for(int i=1;i<=N;i++)
	{
		sum-=1LL*cow[i].second;
		ans+=1LL*sum*cow[i].first*2;
	}
	printf("%lld\n",ans);
	return 0;
}
