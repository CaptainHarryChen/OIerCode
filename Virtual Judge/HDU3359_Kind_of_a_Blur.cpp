#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXL=12,MAXN=105;
const double EPS=1e-6;
typedef double Matrix[MAXN][MAXN];
int fcmp(double a,double b)
{
	double c=a-b;
	if(c<-EPS)
		return -1;
	if(c<EPS)
		return 0;
	return 1;
}
int Gauss(Matrix &A,int n,int m)
{
	int r,c,mxr;
	for(r=c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(int i=r+1;i<=n;i++)
			if(fcmp(fabs(A[mxr][c]),fabs(A[i][c]))<0)
				mxr=i;
		if(fcmp(A[mxr][c],0.0)==0)
		{
			r--;
			continue;
		}
		if(mxr!=r)
			swap(A[mxr],A[r]);
		for(int i=1;i<=n;i++)
			if(i!=r)
				for(int j=m;j>=c;j--)
					A[i][j]-=A[r][j]/A[r][c]*A[i][c];
	}
	return r-1;
}
int H,W,D;
double img[MAXL][MAXL];
Matrix eq;
void Make_eq()
{
	memset(eq,0,sizeof eq);
	for(int i=1;i<=H;i++)
		for(int j=1;j<=W;j++)
		{
			int cnt=0;
			for(int a=1;a<=H;a++)
				for(int b=1;b<=W;b++)
					if(abs(i-a)+abs(j-b)<=D)
					{
						cnt++;
						eq[(i-1)*W+j][(a-1)*W+b]=1.0;
					}
			eq[(i-1)*W+j][H*W+1]=1.0*cnt*img[i][j];
		}
}
int main()
{
	bool flag=false;
	while(true)
	{
		scanf("%d%d%d",&W,&H,&D);
		if(!H&&!W&&!D)
			break;
		if(flag)
			puts("");
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				scanf("%lf",img[i]+j);
		Make_eq();
		Gauss(eq,H*W,H*W+1);
		for(int i=1;i<=H;i++)
		{
			for(int j=1;j<=W;j++)
				printf("%8.2f",eq[(i-1)*W+j][H*W+1]/eq[(i-1)*W+j][(i-1)*W+j]);
			puts("");
		}
		flag=true;
	}
	return 0;
}
