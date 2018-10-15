#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005;
#define y1 kuhgahbidlawslgfuhhfiuhs

int N,M,x1,y1,x2,y2;
pair<int,int> P[MAXN];
int dp[MAXN];

int main()
{
	scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&N);
	for(int i=1;i<=N;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(min(x1,x2)<=x&&x<=max(x1,x2)&&min(y1,y2)<=y&&y<=max(y1,y2))
			P[++M]=make_pair(x,y);
	}
	if(x1>x2)
	{
		swap(x1,x2);
		swap(y1,y2);
	}
	if(y1>y2)
	{
		for(int i=1;i<=M;i++)
			P[i].second=y2+y1-P[i].second;
		swap(y1,y2);
	}
	
	sort(P+1,P+M+1);
	memset(dp,0x3F,sizeof dp);
	dp[0]=-1;
	int lis=0;
	for(int i=1;i<=M;i++)
	{
		int j=upper_bound(dp,dp+M+1,P[i].second)-dp;
		dp[j]=min(dp[j],P[i].second);
		lis=max(lis,j);
	}
	double ans=0;
	ans=100.0*(x2-x1+y2-y1)-20.0*lis+5.0*lis*acos(-1);
	if(lis==min(y2-y1+1,x2-x1+1))
		ans+=5.0*acos(-1);
	printf("%.15lf\n",ans);
	
	return 0;
}
