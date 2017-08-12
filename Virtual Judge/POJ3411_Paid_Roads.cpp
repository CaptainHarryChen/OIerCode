#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=12,MAXS=1<<10;
struct Road
{
	Road(){}
	Road(int _b,int _c,int _P,int _R){b=_b;c=_c;P=_P;R=_R;}
	int b,c,P,R;
};
typedef pair<int,int>State;
vector<Road>V[MAXN];
queue<State>Q;
int dp[MAXS][MAXN];
int main()
{
	int N,m,maxs;
	scanf("%d%d",&N,&m);
	maxs=1<<N;
	for(int i=1,a,b,c,P,R;i<=m;i++)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&P,&R);
		V[a].push_back(Road(b,c,P,R));
	}
	memset(dp,0x3F,sizeof dp);
	dp[1][1]=0;
	Q.push(State(1,1));
	while(!Q.empty())
	{
		State t=Q.front();
		Q.pop();
		int l=(int)V[t.second].size();
		for(int j=0;j<l;j++)
		{
			const Road &r=V[t.second][j];
			int &ndp=dp[t.first|(1<<(r.b-1))][r.b];
			bool update=0;
			if(t.first&(1<<(r.c-1)))
				if(ndp>dp[t.first][t.second]+r.P)
				{
					ndp=dp[t.first][t.second]+r.P;
					update=1;
				}
			if(ndp>dp[t.first][t.second]+r.R)
			{
				ndp=dp[t.first][t.second]+r.R;
				update=1;
			}
			if(update)
				Q.push(State(t.first|(1<<(r.b-1)),r.b));
		}
	}
	int ans=0x3F3F3F3F;
	for(int s=1;s<maxs;s++)
		ans=min(ans,dp[s][N]);
	if(ans==0x3F3F3F3F)
		printf("impossible\n");
	else
		printf("%d\n",ans);
	return 0;
}
