#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXN 20005
#define MAXC 100005
int N,C,F;
int left[MAXC],right[MAXC];
pair<int,int>cow[MAXC];
priority_queue<int>Q1,Q2;
int main()
{
	scanf("%d%d%d",&N,&C,&F);
	for(int i=1;i<=C;i++)
		scanf("%d%d",&cow[i].first,&cow[i].second);
	sort(cow+1,cow+C+1);
	int len=N/2;
	int sum=0;
	for(int i=1;i<=C;i++)
	{
		Q1.push(cow[i].second);
		sum+=cow[i].second;
		if(i>len)
		{
			sum-=Q1.top();
			Q1.pop();
		}
		left[i]=sum;
		if(i<len)
			left[i]=0x3FFFFFFF;
	}
	sum=0;
	for(int i=C;i>=1;i--)
	{
		Q2.push(cow[i].second);
		sum+=cow[i].second;
		if(C-i+1>len)
		{
			sum-=Q2.top();
			Q2.pop();
		}
		right[i]=sum;
		if(C-i+1<len)
			right[i]=0x3FFFFFFF;
	}
	int ans=-1;
	for(int i=C-1;i>1;i--)
		if(cow[i].second+left[i-1]+right[i+1]<=F)
		{ans=cow[i].first;break;}
	printf("%d\n",ans);
	return 0;
}
