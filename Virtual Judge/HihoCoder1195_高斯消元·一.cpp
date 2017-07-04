#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using std::swap;
#define MAXN 505
#define EPS 1e-8
typedef double Matrix[MAXN][MAXN*2];
int n,m;
int Rank;
double X[MAXN];
bool Free[MAXN],flag;
Matrix A;
void Gauss()
{
	int r,c,mxr;
	for(r=1,c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(int i=r+1;i<=n;i++)
			if(fabs(A[i][c])>fabs(A[mxr][c]))
				mxr=i;
		if(fabs(A[mxr][c])<EPS)
		{
			r--;
			flag=1;
			continue;
		}
		if(mxr!=r)swap(A[mxr],A[r]);
		for(int i=1;i<=n;i++)
			if(i!=r&&fabs(A[i][c])>EPS)
				for(int j=m;j>=c;j--)
					A[i][j]-=A[r][j]/A[r][c]*A[i][c];
	}
	Rank=r-1;
}
bool check()
{
	for(int i=Rank+1;i<=n;i++)
		if(fabs(A[i][m])>EPS)
			return 0;
	for(int i=1;i<m;i++)
		Free[i]=1;
	for(int i=Rank,cnt=0,pos;i>0;i--)
	{
		cnt=0;
		for(int j=1;j<m;j++)
			if(Free[j]&&fabs(A[i][j])>EPS)
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
	scanf("%d%d",&m,&n);
	m++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&A[i][j]);
	Gauss();
	if(!check())
		printf("No solutions\n");
	else
	{
		if(flag)
			printf("Many solutions\n");
		else
			for(int i=1;i<m;i++)
				printf("%d\n",(int)(X[i]+0.5));
	}
	return 0;
}
