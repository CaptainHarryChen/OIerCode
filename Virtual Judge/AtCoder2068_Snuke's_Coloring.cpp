#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int H,W,N;
set<pair<int,int> > ans[10],blk;
pair<int,int> P[MAXN];

int Count(pair<int,int> R)
{
	int cnt=0;
	for(int i=R.first;i<R.first+3;i++)
		for(int j=R.second;j<R.second+3;j++)
			cnt+=blk.count(make_pair(i,j));
	return cnt;
}

int main()
{
	scanf("%d%d%d",&H,&W,&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d%d",&P[i].first,&P[i].second);
		if(!blk.count(P[i]))
			blk.insert(P[i]);
	}
	
	for(int i=1;i<=N;i++)
	{
		for(int x=max(P[i].first-2,1);x<=P[i].first&&x+2<=H;x++)
			for(int y=max(P[i].second-2,1);y<=P[i].second&&y+2<=W;y++)
			{
				pair<int,int> r=make_pair(x,y);
				int c=Count(r);
				ans[c].insert(r);
			}
	}
	long long ans0=(1LL*(W-2)*(H-2));
	for(int i=1;i<10;i++)
		ans0-=ans[i].size();
	printf("%lld\n",ans0);
	for(int i=1;i<10;i++)
		printf("%u\n",ans[i].size());
	
	return 0;
}
