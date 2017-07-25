#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int dir[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
int A[35][35];
void init()
{
	for(int i=0;i<5;i++)
		for(int j=0;j<6;j++)
		{
			A[i*6+j][i*6+j]=1;
			for(int d=0,x,y;d<4;d++)
			{
				x=i+dir[d][0],y=j+dir[d][1];
				if(x<0||y<0||x>=5||y>=6)continue;
				A[x*6+y][i*6+j]=1;
			}
		}
}
void Gauss()
{
	int mxr;
	for(int r=0,c=0;r<30&&c<30;r++,c++)
	{
		mxr=r;
		while(!A[mxr][c]&&mxr<30)
			mxr++;
		if(mxr>=30)
		{
			r--;
			continue;
		}
		if(mxr!=r)
			for(int j=0;j<=30;j++)
				swap(A[mxr][j],A[r][j]);
		for(int i=0;i<30;i++)
		{
			if(i==r||!A[i][c])
				continue;
			for(int j=c;j<=30;j++)
				A[i][j]^=A[r][j];
		}
	}
}
void print()
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
			printf("%d ",A[i*6+j][30]);
		printf("%d\n",A[i*6+5][30]);
	}
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		memset(A,0,sizeof A);
		for(int i=0;i<30;i++)
			scanf("%d",A[i]+30);
		init();
		Gauss();
		printf("PUZZLE #%d\n",Case);
		print();
	}
	return 0;
}
