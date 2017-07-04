#include<cstdio>
#include<algorithm>
using namespace std;
#define MAXM 1005
#define MAXN 1000005
int dp[MAXM][MAXM],mx[MAXM],ti[MAXN];
int N,M,R;
struct milk{int st,ed,val;}h[MAXM];
bool cmp(milk a,milk b){return a.ed<b.ed;}
int main()
{
	scanf("%d%d%d",&N,&M,&R);
	for(int i=1;i<=M;i++)
		scanf("%d%d%d",&h[i].st,&h[i].ed,&h[i].val);
	sort(h+1,h+M+1,cmp);
	for(int i=1,j=1;i<=N;ti[i]=h[j].ed<=i?j++:j-1,i++);
	for(int i=1;i<=M;i++)
		for(int j=0;j<=i;j++)
		{
			if(i>j&&h[i-1].ed>=h[j].ed)
				dp[i][j]=max(dp[i][j],dp[i-1][j]);
			if(i==j)
				dp[i][j]=max(dp[i][j],mx[ti[max(h[i].st-R,0)]]+h[i].val);
			mx[i]=max(mx[i],dp[i][j]);
		}
	int ans=0;
	for(int j=0;j<=M;j++)
		ans=max(ans,dp[M][j]);
	printf("%d\n",ans);
	return 0;
}
