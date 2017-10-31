#include<cstdio>
#include<algorithm>
using std::swap;
const long long MAXN=20;
typedef long long Matrix[MAXN][MAXN];
long long gcd(long long a,long long b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}
long long lcm(long long a,long long b)
{return a/gcd(a,b)*b;}
long long Gauss(Matrix &A,long long n,long long m)
{
	long long r,c,mxr;
	for(r=c=1;r<=n&&c<m;r++,c++)
	{
		mxr=r;
		for(long long i=r+1;i<=n;i++)
			if(abs(A[i][c])>abs(A[mxr][c]))
				mxr=i;
		if(A[mxr][c]==0)
		{
			r--;
			continue;
		}
		if(mxr!=r)
			swap(A[mxr],A[r]);
		for(long long i=1;i<=n;i++)
			if(i!=r&&A[i][c]!=0)
			{
				long long l=lcm(abs(A[i][c]),abs(A[r][c]));
				long long a=abs(l/A[i][c]),b=abs(l/A[r][c]);
				long long g=0;
				if(A[i][c]*A[r][c]<0)
					b=-b;
				for(long long j=m;j>=c;j--)
				{
					A[i][j]=A[i][j]*a-A[r][j]*b;
					if(g==0)g=A[i][j];
					else g=gcd(g,A[i][j]);
				}
				if(c>i)
				{
					A[i][i]=A[i][i]*a;
					if(g==0)g=A[i][i];
					else g=gcd(g,A[i][i]);
				}
				if(g)
					for(long long j=1;j<=m;j++)
						A[i][j]/=g;
			}
	}
	return r-1;
}
Matrix eq;
bool fre[MAXN];
long long X[MAXN];
bool check(long long n,long long m,long long num)
{
	for(long long i=num+1;i<=n;i++)
		if(eq[i][m]!=0)
			return false;
	for(long long j=1;j<m;j++)
		fre[j]=true;
	for(long long i=num;i>0;i--)
	{
		long long cnt=0,id;
		for(long long j=1;j<m;j++)
			if(eq[i][j]!=0&&fre[j])
			{
				cnt++;
				id=j;
			}
		if(cnt>1||cnt==0)
			continue;
		long long sum=0;
		for(long long j=1;j<m;j++)
			if(!fre[j])
				sum+=X[j]*eq[i][j];
		X[id]=(eq[i][m]-sum)/eq[i][id];
		fre[id]=false;
	}
	return true;
}
int main()
{
	long long n,m;
	scanf("%lld%lld",&n,&m);
	m++;
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=m;j++)
			scanf("%lld",&eq[i][j]);
	long long num=Gauss(eq,n,m);
	if(!check(n,m,num))
	{
		puts("No solution");
		return 0;
	}
	for(long long i=1;i<m;i++)
		if(fre[i])
			printf("X[%lld] not determined\n",i);
		else
			printf("X[%lld] = %lld\n",i,X[i]);
	return 0;
}
