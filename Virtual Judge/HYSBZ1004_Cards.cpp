#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=23,MAXM=65;

int inv(int a,int p)
{
	int ret=1,b=p-2;
	while(b)
	{
		if(b&1)
			ret=ret*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ret;
}

int n,m,P,R,B,G;
int per[MAXM][MAXM],dp[MAXM][MAXN][MAXN][MAXN];
bool vis[MAXM];
vector<int> rep;

int main()
{
	scanf("%d%d%d%d%d",&R,&B,&G,&m,&P);
	n=R+B+G;
	for(int i=1;i<=n;i++)
		per[1][i]=i;
	for(int i=2;i<=m+1;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&per[i][j]);
	
	int ans=0;
	for(int i=1;i<=m+1;i++)
	{
		memset(vis,0,sizeof vis);
		rep.clear();
		for(int j=1;j<=n;j++)
		{
			if(vis[j])
				continue;
			int u=j,cnt=0;
			while(!vis[u])
			{
				cnt++;
				vis[u]=true;
				u=per[i][u];
			}
			rep.push_back(cnt);
		}
		memset(dp,0,sizeof dp);
		dp[0][0][0][0]=1;
		for(int a=0;a<(int)rep.size();a++)
			for(int r=0;r<=R;r++)
				for(int b=0;b<=B;b++)
					for(int g=0;g<=G;g++)
					{
						if(r>=rep[a])
							(dp[a+1][r][b][g]+=dp[a][r-rep[a]][b][g])%=P;
						if(b>=rep[a])
							(dp[a+1][r][b][g]+=dp[a][r][b-rep[a]][g])%=P;
						if(g>=rep[a])
							(dp[a+1][r][b][g]+=dp[a][r][b][g-rep[a]])%=P;
					}
		(ans+=dp[rep.size()][R][B][G])%=P;
	}
	ans=ans*inv(m+1,P)%P;
	printf("%d\n",ans);
	
	return 0;
}
