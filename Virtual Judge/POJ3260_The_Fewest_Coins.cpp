#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=105,MAXT=30005;

int N,T;
int V[MAXN],C[MAXN];
int dp1[MAXT],dp2[MAXT];

int main()
{
	scanf("%d%d",&N,&T);
	for(int i=1;i<=N;i++)
		scanf("%d",V+i);
	for(int i=1;i<=N;i++)
		scanf("%d",C+i);
	
	memset(dp1,0x3F,sizeof dp1);
	dp1[0]=0;
	for(int i=1;i<=N;i++)
	{
		for(int k=1;C[i];k<<=1)
		{
			k=min(k,C[i]);
			int v=k*V[i];
			for(int j=MAXT-1;j>=v;j--)
				dp1[j]=min(dp1[j],dp1[j-v]+k);
			C[i]-=k;
		}
	}
	memset(dp2,0x3F,sizeof dp2);
	dp2[0]=0;
	for(int i=1;i<=N;i++)
		for(int j=V[i];j<MAXT;j++)
			dp2[j]=min(dp2[j],dp2[j-V[i]]+1);
	
	int ans=0x3F3F3F3F;
	for(int i=T;i<MAXT;i++)
		ans=min(ans,dp1[i]+dp2[i-T]);
	if(ans==0x3F3F3F3F)
		ans=-1;
	printf("%d\n",ans);
	
	return 0;
}
