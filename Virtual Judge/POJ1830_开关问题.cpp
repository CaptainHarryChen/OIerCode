#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=33;
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
Matrix eq;
int st[MAXN],ed[MAXN];
int main()
{
	int K,N,a,b;
	scanf("%d",&K);
	while(K--)
	{
		memset(eq,0,sizeof eq);
		scanf("%d",&N);
		for(int i=1;i<=N;i++)
			scanf("%d",st+i);
		for(int i=1;i<=N;i++)
		{
			scanf("%d",ed+i);
			eq[i][N+1]=st[i]^ed[i];
		}
		for(int i=1;i<=N;i++)
			eq[i][i]=1;
		while(true)
		{
			scanf("%d%d",&a,&b);
			if(a==0&&b==0)
				break;
			eq[b][a]=1;
		}
		int Rank=Gauss(eq,N,N+1);
		bool flag=true;
		for(int i=Rank+1;i<=N;i++)
			if(eq[i][N+1])
			{flag=false;break;}
		if(flag)
			printf("%d\n",1<<(N-Rank));
		else
			puts("Oh,it's impossible~!!");
	}
	return 0;
}
