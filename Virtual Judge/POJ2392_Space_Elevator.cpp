#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXK 405
#define MAXA 400005
int K;
struct block{int h,a,c;}bl[MAXK];
bool cmp(block a,block b){return a.a<b.a;}
bool dp[MAXA];
int main()
{
	scanf("%d",&K);
	int mxh=0;
	for(int i=1;i<=K;i++)
	{
		scanf("%d%d%d",&bl[i].h,&bl[i].a,&bl[i].c);
		mxh=max(mxh,bl[i].a);
	}
	sort(bl+1,bl+K+1,cmp);
	dp[0]=1;
	for(int i=1;i<=K;i++)
	{
		int k=1,c=bl[i].c;
		while(k<c)
		{
			for(int j=bl[i].a-bl[i].h*k;j>=0;j--)
				dp[j+bl[i].h*k]|=dp[j];
			c-=k;
			k<<=1;
		}
		for(int j=bl[i].a-bl[i].h*c;j>=0;j--)
			dp[j+bl[i].h*c]|=dp[j];
	}
	int ans=0;
	for(int i=0;i<=mxh;i++)
		if(dp[i])
			ans=i;
	printf("%d\n",ans);
	return 0;
}
 