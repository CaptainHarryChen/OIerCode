#include<cstdio>
#include<cmath>
#include<algorithm>
using std::swap;
#define MAXN 405
#define EPS 1e-8
typedef double Matrix[MAXN][MAXN];
int n,m;
int Rank;
double X[MAXN];
bool Free[MAXN];
Matrix A;
int fcmp(double a,double b)
{
	if((a-b)>EPS)
		return 1;
	else if((a-b)>-EPS)
		return 0;
	return -1;
}
void Gauss()
{
	int r,c,mxr;
	for(r=1,c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(int i=r+1;i<=n;i++)
			if(fcmp(fabs(A[i][c]),fabs(A[mxr][c]))>0)
				mxr=i;
		if(fcmp(A[mxr][c],0.0)==0)
		{r--;continue;}
		if(mxr!=r)swap(A[mxr],A[r]);
		for(int i=1;i<=n;i++)
			if(i!=r&&fcmp(A[i][c],0.0)!=0)
				for(int j=m;j>=c;j--)
					A[i][j]-=A[r][j]/A[r][c]*A[i][c];
	}
	Rank=r-1;
}
bool check()
{
	for(int i=Rank+1;i<=n;i++)
		if(fcmp(A[i][m],0.0)!=0)
			return 0;
	for(int i=1;i<m;i++)
		Free[i]=1;
	for(int i=Rank,cnt=0,pos;i>0;i--)
	{
		cnt=0;
		for(int j=1;j<m;j++)
			if(Free[j]&&fcmp(A[i][j],0.0)!=0)
				cnt++,pos=j;
		if(cnt==1)
		{
			Free[pos]=0;
			X[pos]=A[i][m]/A[i][pos];
		}
	}
	return 1;
}
int main()
{
	freopen("Gauss_data.in","r",stdin);
	scanf("%d%d",&n,&m);
	m++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&A[i][j]);
	Gauss();
	if(!check())
		printf("No solution\n");
	else
	{
		if(Rank<m-1)
		{
			printf("Multiple solution, free_num: %d\n",m-1-Rank);
			for(int i=1;i<m;i++)
				if(Free[i])
					printf("X[%d] not determined\n",i);
				else
					printf("X[%d] = %.4lf\n",i,X[i]);
		}
		else
			for(int i=1;i<m;i++)
				printf("X[%d] = %.4lf\n",i,X[i]);
	}
	return 0;
}
