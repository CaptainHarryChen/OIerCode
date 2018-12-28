#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=1030,MOD=1000000007,INV2=(MOD+1)/2;

int n,m;
vector<int> adj[MAXN];
int val[MAXN];
int dp[MAXN][MAXN];

void FWT(int A[],int n,int mode)
{
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)
			swap(A[i],A[j]);
		int k=n>>1;
		while(k&j)
			j^=k,k>>=1;
		j^=k;
	}
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int l=j,r=j+i;l<j+i;l++,r++)
			{
				int a=A[l],b=A[r];
				A[l]=(a+b)%MOD;
				A[r]=(a-b+MOD)%MOD;
				if(mode==-1)
				{
					A[l]=1LL*A[l]*INV2%MOD;
					A[r]=1LL*A[r]*INV2%MOD;
				}
			}
}

void XorMul(const int A[],const int B[],int C[],int len)
{
	static int tA[MAXN],tB[MAXN],res[MAXN];
	for(int i=0;i<len;i++)
		tA[i]=A[i],tB[i]=B[i];
	FWT(tA,len,1);FWT(tB,len,1);
	for(int i=0;i<len;i++)
		res[i]=1LL*tA[i]*tB[i]%MOD;
	FWT(res,len,-1);
	for(int i=0;i<len;i++)
		C[i]=res[i];
}

void DP(int u,int fa=0)
{
	memset(dp[u],0,sizeof dp[u]);
	dp[u][val[u]]=1;
	for(int i=0;i<(int)adj[u].size();i++)
	{
		int v=adj[u][i];
		if(v==fa)
			continue;
		DP(v,u);
		dp[v][0]++;
		XorMul(dp[u],dp[v],dp[u],m);
		dp[v][0]--;
	}
}

int ans[MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			scanf("%d",&val[i]);
		for(int i=1;i<=n;i++)
			adj[i].clear();
		for(int i=1;i<n;i++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		DP(1);
		memset(ans,0,sizeof ans);
		for(int i=1;i<=n;i++)
			for(int j=0;j<m;j++)
				ans[j]=(ans[j]+dp[i][j])%MOD;
		for(int i=0;i<m;i++)
			printf("%d%c",ans[i]," \n"[i==m-1]);
	}
	
	return 0;
}
