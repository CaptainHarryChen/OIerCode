#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXC 2505
#define MAXSPF 1005
int C,L;
pair<int,int>cow[MAXC];
pair<int,int>lo[MAXC];
priority_queue<int,vector<int>,greater<int> >Q;
int main()
{
	scanf("%d%d",&C,&L);
	for(int i=1;i<=C;i++)
		scanf("%d%d",&cow[i].first,&cow[i].second);
	sort(cow+1,cow+C+1);
	for(int i=1;i<=L;i++)
		scanf("%d%d",&lo[i].first,&lo[i].second);
	sort(lo+1,lo+L+1);
	int ans=0,l=0;
	for(int i=1;i<=L;i++)
	{
		for(;l<=C&&cow[l].first<=lo[i].first;l++)
			Q.push(cow[l].second);
		while(!Q.empty()&&lo[i].second)
		{
			int t=Q.top();
			Q.pop();
			if(t<lo[i].first)
				continue;
			ans++;
			lo[i].second--;
		}
	}
	printf("%d\n",ans);
	return 0;
}
