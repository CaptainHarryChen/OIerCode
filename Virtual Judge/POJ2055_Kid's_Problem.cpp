#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXK=100,MAXN=100;
typedef int Matrix[MAXK][MAXK];
int pow_mod(int a,int b,int p)
{
	int ret=1;
	while(b)
	{
		if(b&1)
			ret=(ret*a)%p;
		a=(a*a)%p;
		b>>=1;
	}
	return ret;
}
int gcd(int a,int b)
{return b==0?a:gcd(b,a%b);}
int lcm(int a,int b)
{return a/gcd(a,b)*b;}
int inv(int a,int p)
{return pow_mod(a,p-2,p);}
int Gauss(Matrix &A,int n,int m,int p)
{
	int r,c,mxr;
	for(r=c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(int i=r+1;i<=n;i++)
			if(A[i][c])
				mxr=i;
		if(A[mxr][c]==0)
		{r--;continue;}
		if(mxr!=r)
			for(int j=1;j<=m;j++)
				swap(A[r][j],A[mxr][j]);
		for(int i=r+1;i<=n;i++)
			while(A[i][c])
			{
				int t=A[r][c]/A[i][c];
				for(int j=c;j<=m;j++)
					A[r][j]=((A[r][j]-A[i][j]*t)%p+p)%p;
				for(int j=c;j<=m;j++)
					swap(A[r][j],A[i][j]);
			}
	}
	return r-1;
}
int ans,X[MAXK];
Matrix eq;
void dfs(int id,int sum,int K,int N)
{
	if(id<=0)
	{
		ans=min(ans,sum);
		return;
	}
	for(int i=0,s;i<N;i++)
	{
		if(i+sum>=ans)break;
		s=0;
		X[id]=i;
		for(int j=1;j<=K;j++)
			s=(s+eq[id][j]*X[j])%N;
		if(s==eq[id][K+1])
			dfs(id-1,sum+i,K,N);
		X[id]=0;
	}
}
int main()
{
	int K,N;
	while(true)
	{
		scanf("%d%d",&K,&N);
		if(K==0&&N==0)
			break;
		memset(eq,0,sizeof eq);
		memset(X,0,sizeof X);
		ans=0x7FFFFFFF;
		for(int i=1;i<=K;i++)
		{
			scanf("%d",&eq[i][K+1]);
			eq[i][K+1]=(N+1-eq[i][K+1])%N;
		}
		for(int i=1,p;i<=K;i++)
		{
			scanf("%d",&p);
			for(int j=1,a,b;j<=p;j++)
			{
				scanf("%d%d",&a,&b);
				eq[a][i]=b%N;
			}
		}
		int R=Gauss(eq,K,K+1,N);
		bool flag=true;
		for(int i=R+1;i<=K;i++)
			if(eq[i][K+1])
			{flag=false;break;}
		if(!flag)
			puts("No solution");
		else
		{
			ans=0x7FFFFFFF;
			dfs(K,0,K,N);
			if(ans==0x7FFFFFFF)
				puts("No solution");
			else
				printf("%d\n",ans);
		}
	}
	return 0;
}
