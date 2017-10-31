#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=405;
const double EPS=1e-8;
typedef double Matrix[MAXN][MAXN];
int fcmp(double a,double b)
{
	double t=a-b;
	if(t<-EPS)return -1;
	if(t<EPS)return 0;
	return 1;
}
int Gauss(Matrix &A,int n,int m)
{
	int r,c,mxr;
	for(r=c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(int i=r+1;i<=n;i++)
			if(fcmp(fabs(A[i][c]),fabs(A[mxr][c]))==1)
				mxr=i;
		if(fcmp(A[mxr][c],0.0)==0)
		{
			r--;
			continue;
		}
		if(mxr!=r)
			swap(A[mxr],A[r]);
		for(int i=1;i<=n;i++)
			if(i!=r&&fcmp(A[i][c],0.0)!=0)
				for(int j=m;j>=c;j--)
					A[i][j]-=A[r][j]/A[r][c]*A[i][c];
	}
	return r-1;
}
Matrix eq;
bool fre[MAXN];
double X[MAXN];
bool check(int n,int m,int num)
{
	for(int i=num+1;i<=n;i++)
		if(fcmp(eq[i][m],0.0)!=0)
			return false;
	for(int j=1;j<m;j++)
		fre[j]=true;
	for(int i=num;i>0;i--)
	{
		int cnt=0,id;
		for(int j=1;j<m;j++)
			if(fcmp(eq[i][j],0.0)!=0&&fre[j])
			{
				cnt++;
				id=j;
			}
		if(cnt==1)
		{
			double sum=0.0;
			for(int j=1;j<m;j++)
				if(!fre[j])
					sum+=X[j]*eq[i][j];
			X[id]=(eq[i][m]-sum)/eq[i][id];
			fre[id]=false;
		}
	}
	return true;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	m++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%lf",&eq[i][j]);
	int num=Gauss(eq,n,m);
	if(!check(n,m,num))
	{
		puts("No solution");
		return 0;
	}
	for(int i=1;i<m;i++)
		if(fre[i])
			printf("X[%d] not determined\n",i);
		else
		{
			if(fcmp(X[i],0.0)==0)
				X[i]=0.0;
			printf("X[%d] = %.4lf\n",i,X[i]);
		}
	return 0;
}
