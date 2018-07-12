#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=15;

struct Matrix
{
	int sz;
	long long A[MAXN][MAXN];
	Matrix(int _sz=MAXN-1):sz(_sz)
	{
		for(int i=1;i<=sz;i++)
			for(int j=1;j<=sz;j++)
				A[i][j]=(i==j);
	}
	void Clear(int _sz)
	{
		memset(A,0,sizeof A);
		sz=_sz;
	}
	long long* operator [] (int i)
	{return A[i];}
	long long Det()
	{
		long long ret=1;
		int r=2,c=2;
		for(;r<=sz&&c<=sz;r++,c++)
		{
			int mxr=r;
			while(A[mxr][c]==0&&mxr<=sz)
				mxr++;
			if(mxr>sz)
				return 0;
			if(r!=mxr)
			{
				for(int j=1;j<=sz;j++)
					swap(A[mxr][j],A[r][j]);
			}
			for(int i=r+1;i<=sz;i++)
				while(A[i][c]!=0)
				{
					long long k=A[i][c]/A[r][c];
					for(int j=c;j<=sz;j++)
						A[i][j]-=k*A[r][j];
					if(A[i][c]==0)
						break;
					for(int j=1;j<=sz;j++)
						swap(A[i][j],A[r][j]);
				}
		}
		for(int i=2;i<=sz;i++)
			ret*=A[i][i];
		if(ret<0)
			ret=-ret;
		return ret;
	}
};

Matrix A;

int main()
{
	int T,n,m,u,v;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		A.Clear(n);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&u,&v);
			A[u][v]=A[v][u]=-1;
			A[u][u]++;
			A[v][v]++;
		}
		printf("%lld\n",A.Det());
	}
	
	return 0;
}
