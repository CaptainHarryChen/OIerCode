#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXN 105
pair<int,int> sa[MAXN],sb[MAXN];
int NA,NB,N,T;
int main()
{
	scanf("%d",&N);
	for(int Case=1;Case<=N;Case++)
	{
		scanf("%d%d%d",&T,&NA,&NB);
		for(int i=1,h,m;i<=NA;i++)
		{
			scanf("%d:%d",&h,&m);
			sa[i].first=h*60+m;
			scanf("%d:%d",&h,&m);
			sa[i].second=h*60+m;
		}
		for(int i=1,h,m;i<=NB;i++)
		{
			scanf("%d:%d",&h,&m);
			sb[i].first=h*60+m;
			scanf("%d:%d",&h,&m);
			sb[i].second=h*60+m;
		}
		int cnta=0,cntb=0;
		priority_queue<int,vector<int>,greater<int> >sta,stb;
		for(int i=0;i<1440;i++)
		{
			for(int j=1;j<=NA;j++)
				if(sa[j].first==i)
				{
					if(sta.empty()||sta.top()>sa[j].first)
						cnta++;
					else
						sta.pop();
					stb.push(sa[j].second+T);
				}
			for(int j=1;j<=NB;j++)
				if(sb[j].first==i)
				{
					if(stb.empty()||stb.top()>sb[j].first)
						cntb++;
					else
						stb.pop();
					sta.push(sb[j].second+T);
				}
		}
		printf("Case #%d: %d %d\n",Case,cnta,cntb);
	}
	return 0;
}
