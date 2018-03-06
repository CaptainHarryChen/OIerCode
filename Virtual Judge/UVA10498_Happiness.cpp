#include<cstdio>
#include<cmath>
const int MAXN=23;
const double EPS=1e-8;

int n,m;
double A[MAXN][MAXN],B[MAXN],C[MAXN],ans;

int fcmp(double a,double b)
{
	if(fabs(a-b)<EPS)
		return 0;
	if(a<b)return -1;
	return 1;
}

void pivot(int r,int c)
{
	for(int i=1;i<=m;i++)
		if(i!=r)
		{
			for(int j=1;j<=n;j++)
				if(j!=c)
					A[i][j]-=A[r][j]*A[i][c]/A[r][c];
			B[i]-=B[r]*A[i][c]/A[r][c];
		}
	for(int j=1;j<=n;j++)
		if(j!=c)
			A[r][j]/=A[r][c];
	B[r]/=A[r][c];
	for(int i=1;i<=m;i++)
		if(i!=r)
			A[i][c]/=-A[r][c];
	A[r][c]=1.0/A[r][c];
	//swap(
	ans+=B[r]*C[c];
	for(int j=1;j<=n;j++)
		if(j!=c)
			C[j]-=C[c]*A[r][j];
	C[c]*=-A[r][c];
}

void simplex()
{
	ans=0;
	int r,c;
	double best1,best2;
	for(;;)
	{
		r=c=-1;
		best1=-1e20;
		for(int i=1,tr=-1;i<=n;i++)
			if(fcmp(C[i],0)==1)
			{
				best2=1e20;
				for(int j=1;j<=m;j++)
					if(fcmp(A[j][i],0)==1)
						if(fcmp(B[j]/A[j][i],best2)==-1)
							best2=B[j]/A[j][i],tr=j;
				if(fcmp(best1,best2*C[i])==-1)
					best1=best2*C[i],c=i,r=tr;
			}
		if(r==-1||c==-1)
			break;
		pivot(r,c);
	}
}

int main()
{
	while(scanf("%d%d",&n,&m)==2)
	{
		for(int i=1;i<=n;i++)
			scanf("%lf",C+i);
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
				scanf("%lf",A[i]+j);
			scanf("%lf",B+i);
		}
	
		simplex();
		
		printf("Nasa can spend %d taka.\n",(int)ceil(ans*m));
	}
	return 0;
}
