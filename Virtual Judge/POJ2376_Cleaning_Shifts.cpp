#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXN 25005
int N,T;
struct cow
{
	int s,e;
	bool operator < (const cow &t)const
	{return s<t.s||(s==t.s&&e<t.e);}
}c[MAXN];
int main()
{
	scanf("%d%d",&N,&T);
	for(int i=1;i<=N;i++)
		scanf("%d%d",&c[i].s,&c[i].e);
	sort(c+1,c+N+1);
	int now=1,ans=0,mx,i=1;
	while(now<=T)
	{
		mx=-1;
		for(;i<=N&&c[i].s<=now;i++)
			mx=max(mx,c[i].e);
		if(mx==-1)
		{printf("-1\n");return 0;}
		ans++;
		now=mx+1;
	}
	printf("%d\n",ans);
	return 0;
}
