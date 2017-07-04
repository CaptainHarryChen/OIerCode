#include<cstdio>
#include<algorithm>
using std::sort;
using std::swap;
using std::pair;
#define MAXN 55
bool cmp(pair<int,int>a,pair<int,int>b)
{
	int temp=a.first*b.second-b.first*a.second;
	return temp>0;
}
int main()
{
	int n=0;
	pair<int,int>point[MAXN];
	while(~scanf("%d%d",&point[n].first,&point[n].second))
	{
		if(point[n].first==0&&point[n].second==0)
			swap(point[0],point[n]);
		n++;
	}
	sort(point+1,point+n,cmp);
	for(int i=0;i<n;i++)
		printf("(%d,%d)\n",point[i].first,point[i].second);
	return 0;
}
