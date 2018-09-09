#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=305,MAXLOG=10;

struct Matrix
{
	int n,A[MAXN][MAXN];
	Matrix(int _n=1)
	{
		n=_n;
		memset(A,0x3F,sizeof A);
	}
	int* operator [] (int i)
	{return A[i];}
	const int * operator [](int i)const
	{return A[i];}
	Matrix operator * (const Matrix &B)const
	{
		Matrix ret(n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++)
					if(A[i][k]!=0x3F3F3F3F&&B[k][j]!=0x3F3F3F3F)
						ret[i][j]=min(ret[i][j],A[i][k]+B[k][j]);
		return ret;
	}
	void Debug()
	{
		printf("Debug begin----------\n");
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				if(A[i][j]==0x3F3F3F3F)
					printf(" * ");
				else
					printf("%2d ",A[i][j]);
			puts("");
		}
		printf("Debug end------------\n");
	}
};

int n,m;
Matrix dis[MAXLOG],tmp,tmp2;

int main()
{
	freopen("circle.in","r",stdin);
	freopen("circle.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i=0;(1<<i)<=n;i++)
	{
		dis[i].n=n;
		for(int j=1;j<=n;j++)
			dis[i][j][j]=0;
	}
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		dis[0][u][v]=w;
	}
	for(int i=1;(1<<i)<=n;i++)
		dis[i]=dis[i-1]*dis[i-1];//dis[i].Debug();
	tmp.n=n;
	for(int i=1;i<=n;i++)
		tmp[i][i]=0;
	int ans=0;
	for(int i=MAXLOG-1;i>=0;i--)
		if((1<<i)<=n)
		{
			tmp2=tmp*dis[i];
			bool flag=false;
			for(int j=1;j<=n&&!flag;j++)
				if(tmp2[j][j]<0)
					flag=true;
			if(flag)
				continue;
			ans+=(1<<i);
			tmp=tmp2;
			//tmp.Debug();
		}
	ans++;
	if(ans>=n)
		ans=0;
	printf("%d\n",ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
