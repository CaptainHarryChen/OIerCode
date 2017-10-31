#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=205;
const double EPS=1e-8;
typedef double Matrix[MAXN][MAXN*2];
int fcmp(double a,double b)
{
	double t=a-b;
	if(t<-EPS)return -1;
	if(t<EPS)return 0;
	return 1;
}
bool Gauss(Matrix &A,int n,int m)
{
	int r,c,mxr;
	for(r=c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(int i=r+1;i<=n;i++)
			if(fcmp(fabs(A[i][c]),fabs(A[mxr][c]))==1)
				mxr=i;
		if(fcmp(A[mxr][c],0.0)==0)
			return false;
		if(mxr!=r)
			for(int j=1;j<=m;j++)
				swap(A[mxr][j],A[r][j]);
		for(int i=1;i<=n;i++)
			if(i!=r&&fcmp(A[i][c],0.0)!=0)
				for(int j=m;j>=c;j--)
					A[i][j]-=A[r][j]/A[r][c]*A[i][c];
	}
	return true;
}
Matrix eq;
bool G[MAXN][MAXN];
int deg[MAXN],id[MAXN];
int main()
{
	int T,n,m,a,b,var;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		memset(G,0,sizeof G);
		memset(deg,0,sizeof deg);
		memset(eq,0,sizeof eq);
		memset(id,0,sizeof id);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			a++;b++;
			if(G[a][b]==false)
				deg[a]++;
			G[a][b]=true;
		}
		for(int i=1;i<n;i++)
		{
			eq[i][i]=-1.0;
			for(int j=1;j<=n;j++)
				if(G[j][i])
					eq[i][j]=1.0/deg[j];
		}
		var=n+1;
		for(int i=1;i<n;i++)
			if(!G[n][i])
			{
				for(int j=1;j<n;j++)
					if(G[n][j]||i==j)
						eq[j][var]=1.0/(deg[n]+1);
				id[var]=i;
				var++;
			}
		for(int j=1;j<=var;j++)
			eq[n][j]=1.0;
		if(!Gauss(eq,n,var))
		{
			puts("INF");
			continue;
		}
		printf("1 ");
		int ans=0;
		double rp=eq[n][var]/eq[n][n];
		for(int i=n+1;i<var;i++)
			if(rp<eq[n][var]/eq[n][i])
			{
				rp=eq[n][var]/eq[n][i];
				ans=id[i];
			}
		printf("%d\n",ans-1);
	}
	return 0;
}
