#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=2005;

int m,n;
int mat[MAXN][MAXN];
int h[MAXN],l[MAXN],r[MAXN];
int stk[MAXN],tp;

int main()
{
	while(scanf("%d%d",&m,&n)!=EOF)
	{
		int ans=0;
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&mat[i][j]);
		memset(h,0,sizeof h);
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(mat[i][j])
					h[j]++;
				else
					h[j]=0;
			}
			l[1]=1;
			stk[tp=1]=1;
			for(int j=2;j<=n;j++)
			{
				while(tp>0&&h[stk[tp]]>=h[j])
					tp--;
				l[j]=tp==0?1:stk[tp]+1;
				stk[++tp]=j;
			}
			r[n]=n;
			stk[tp=1]=n;
			for(int j=n-1;j>0;j--)
			{
				while(tp>0&&h[stk[tp]]>=h[j])
					tp--;
				r[j]=tp==0?n:stk[tp]-1;
				stk[++tp]=j;
			}
			for(int j=1;j<=n;j++)
				ans=max(ans,(r[j]-l[j]+1)*h[j]);
		}
		printf("%d\n",ans);
	}
	
	return 0;
}
