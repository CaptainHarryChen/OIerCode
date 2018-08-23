#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXL=33;

int N,M;
int A[MAXN],B[MAXL];
int dp[MAXN][MAXL];
pair<int,int> path[MAXN][MAXL],C[MAXN];

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=1;i<=N;i++)
			scanf("%1d",&A[i]);
		int ans=0,ansl,ansr;
		for(int x=0;x<10;x++)
			for(int y=x;y<10;y++)
			{
				M=0;
				int l,r;
				for(int i=0;i<=x;i++)
					B[++M]=i;
				l=M+1;
				for(int i=y;i>=x;i--)
					B[++M]=i;
				r=M;
				for(int i=y;i<10;i++)
					B[++M]=i;
				for(int i=1;i<=N;i++)
					for(int j=1;j<=M;j++)
					{
						if(dp[i][j-1]<dp[i-1][j]+(A[i]==B[j]))
						{
							dp[i][j]=dp[i-1][j]+(A[i]==B[j]);
							path[i][j]=make_pair(i-1,j);
						}
						else
						{
							dp[i][j]=dp[i][j-1];
							path[i][j]=make_pair(i,j-1);
						}
					}
				if(dp[N][M]>ans)
				{
					ans=dp[N][M];
					int p=N,q=M,top=ans;
					ansl=-1,ansr=-1;
					pair<int,int> t;
					while(p&&q)
					{
						t=path[p][q];
						if(dp[t.first][t.second]+1==dp[p][q]&&A[p]==B[q])
							C[top--]=make_pair(p,q);
						p=t.first;
						q=t.second;
					}
					int k;
					for(k=1;k<=ans&&C[k].second<l;k++);
					ansl=C[k].first;
					for(;k<=ans&&C[k].second<=r;k++);
					ansr=C[k-1].first;
					if(ansl>ansr)
						ansl=ansr=1;
				}
			}
		printf("%d %d %d\n",ans,ansl,ansr);
	}
	
	return 0;
}