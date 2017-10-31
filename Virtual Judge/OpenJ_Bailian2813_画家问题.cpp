#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXS=20,MAXN=230;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
typedef int Matrix[MAXN][MAXN];
int Gauss(Matrix &A,int n,int m)
{
	int r,c,mxr;
	for(r=c=1;r<=n&&c<m;r++,c++)
	{
		for(mxr=r;mxr<=n&&A[mxr][c]==0;mxr++);
		if(mxr>n)
		{
			r--;
			continue;
		}
		if(r!=mxr)
			for(int j=1;j<=m;j++)
				swap(A[r][j],A[mxr][j]);
		for(int i=1;i<=n;i++)
			if(i!=r&&A[i][c])
				for(int j=1;j<=m;j++)
					A[i][j]^=A[r][j];
	}
	return r-1;
}
char lig[MAXS][MAXS];
Matrix eq;
int N,ans;
int encode(int x,int y)
{return (x-1)*N+y;}
bool check(int x,int y)
{return x>0&&y>0&&x<=N&&y<=N;}
int X[MAXN],Rank;
int Count()
{
	int ret=0;
	for(int i=1;i<=Rank;i++)
	{
		int sum=eq[i][N*N+1];
		for(int j=Rank+1;j<=N*N;j++)
			sum^=eq[i][j]*X[j];
		for(int j=1;j<=Rank;j++)
			if(eq[i][j]&&X[j]==-1)
				ret+=sum;
	}
	return ret;
}
void dfs(int id,int cnt=0)
{
	if(cnt>=ans)
		return;
	if(id>N*N)
	{
		ans=min(ans,cnt+Count());
		return;
	}
	X[id]=1;
	dfs(id+1,cnt+1);
	X[id]=0;
	dfs(id+1,cnt);
	X[id]=-1;
}
int main()
{
	scanf("%d",&N);
	memset(eq,0,sizeof eq);
	for(int i=1;i<=N;i++)
		scanf("%s",lig[i]+1);
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
		{
			eq[encode(i,j)][encode(i,j)]=1;
			for(int d=0;d<4;d++)
			{
				int a=i+dir[d][0];
				int b=j+dir[d][1];
				if(!check(a,b))
					continue;
				eq[encode(i,j)][encode(a,b)]=1;
			}
			eq[encode(i,j)][N*N+1]=(lig[i][j]=='w');
		}
	Rank=Gauss(eq,N*N,N*N+1);
	bool flag=true;
	for(int i=Rank+1;i<=N*N;i++)
		if(eq[i][N*N+1])
		{flag=false;break;}
	if(flag)
	{
		memset(X,-1,sizeof X);
		ans=0x7FFFFFFF;
		dfs(Rank+1);
		printf("%d\n",ans);
	}
	else
		puts("inf");
	return 0;
}
