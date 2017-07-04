#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAXSIZE 12
#define MAXN 105
#define EPS 1e-6
int W,H,D,Rank;
double Img[MAXSIZE][MAXSIZE];
double A[MAXN][MAXN];
void Gauss()
{
	int r,c,n=W*H,m=W*H+1;
	int mxr;
	for(r=1,c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(int i=r+1;i<=n;i++)
			if(fabs(A[i][c])-fabs(A[mxr][c])>EPS)
				mxr=i;
		if(fabs(A[mxr][c])<EPS)
		{r--;continue;}
		if(mxr!=r)
			swap(A[mxr],A[r]);
		for(int i=1;i<=n;i++)
			if(i!=r&&fabs(A[i][c])>0)
				for(int j=m;j>=c;j--)
					A[i][j]-=A[r][j]*A[i][c]/A[r][c];
	}
	Rank=r-1;
}
inline int Code(int x,int y)
{return (x-1)*W+y;}
int main()
{
	int test=0;
	while(1)
	{
		memset(A,0,sizeof A);
		memset(Img,0,sizeof Img);
		W=H=D=Rank=0;
		scanf("%d%d%d",&W,&H,&D);
		if(!W&&!H&&!D)break;
		if(test++)printf("\n");
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
				scanf("%lf",&Img[i][j]);
		for(int i=1;i<=H;i++)
			for(int j=1;j<=W;j++)
			{
				int cnt=0,id=Code(i,j);
				for(int p=i-D;p<=i+D;p++)
				{
					if(p<=0||p>H)continue;
					int d=(D-abs(i-p));
					for(int q=j-d;q<=j+d;q++)
					{
						if(q<=0||q>W)continue;
						cnt++;
						A[id][Code(p,q)]=1;
					}
				}
				A[id][H*W+1]=cnt*Img[i][j];
			}
		Gauss();
		for(int i=1;i<=H;i++)
		{
			for(int j=1;j<=W;j++)
				printf("%8.2f",A[Code(i,j)][H*W+1]/A[Code(i,j)][Code(i,j)]);
			printf("\n");
		}
	}
	return 0;
}
