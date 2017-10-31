#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5,M=6,MAXN=33;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
typedef int Matrix[MAXN][MAXN];
int encode(int x,int y)
{return (x-1)*M+y;}
bool check(int x,int y)
{return x>0&&y>0&&x<=N&&y<=M;}
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
	return r+1;
}
int lig[N+2][M+2];
Matrix eq;
int main()
{
	int T;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		for(int i=1;i<=N;i++)
			for(int j=1;j<=M;j++)
				scanf("%d",&lig[i][j]);
		memset(eq,0,sizeof eq);
		for(int i=1;i<=N;i++)
			for(int j=1;j<=M;j++)
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
				eq[encode(i,j)][N*M+1]=lig[i][j];
			}
		Gauss(eq,N*M,N*M+1);
		printf("PUZZLE #%d\n",Case);
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=M;j++)
				printf("%d ",eq[encode(i,j)][N*M+1]);
			puts("");
		}
	}
	return 0;
}
