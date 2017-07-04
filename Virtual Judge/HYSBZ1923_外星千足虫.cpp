#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using std::max;
using std::swap;
#define MAXM 1005
#define MAXN 2005
int n,m;
typedef bool Matrix[MAXN][MAXM];
Matrix A;
void Gauss()
{
	int r,c,mxr,mxswap=1;
	for(r=1,c=1;r<=n&&c<m;r++,c++)
	{
		for(mxr=r;!A[mxr][c]&&mxr<=n;mxr++);
		if(mxr>n){r--;continue;}
		if(mxr!=r)swap(A[mxr],A[r]);
		mxswap=max(mxswap,mxr);
		for(int i=1;i<=n;i++)
			if(i!=r&&A[i][c])
				for(int j=1;j<=m;j++)
					A[i][j]^=A[r][j];
	}
	r--;
	if(r<m-1)
	{printf("Cannot Determine\n");return;}
	printf("%d\n",mxswap);
	for(int i=1;i<m;i++)
		if(A[i][m])
			printf("?y7M#\n");
		else
			printf("Earth\n");
}
int main()
{
	scanf("%d%d",&m,&n);
	m++;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<m;j++)
			scanf("%1d",&A[i][j]);
		scanf("%d",&A[i][m]);
	}
	Gauss();
	return 0;
}
