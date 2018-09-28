#include<cstdio>
#include<algorithm>
using namespace std;
const long long MAXN=1005,SIZE=5,MOD=1000000007;

long long PowMod(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1)
			res=1LL*res*a%MOD;
		a=1LL*a*a%MOD;
		b>>=1;
	}
	return res;
}

struct Matrix
{
	long long n,A[SIZE][SIZE];

	long long * operator [] (long long i)
	{return A[i];}
	const long long * operator [] (long long i)const
	{return A[i];}
	
	Matrix operator * (const Matrix &B)const
	{
		Matrix res;
		res.n=n;
		for(long long i=1;i<=n;i++)
			for(long long j=1;j<=n;j++)
				res[i][j]=0;
		for(long long i=1;i<=n;i++)
			for(long long j=1;j<=n;j++)
				for(long long k=1;k<=n;k++)
					res[i][j]=(res[i][j]+1LL*A[i][k]*B[k][j])%MOD;
		return res;
	}
	Matrix Pow(long long x)
	{
		Matrix res;
		res.n=n;
		for(long long i=1;i<=n;i++)
			for(long long j=1;j<=n;j++)
				res[i][j]=0;
		for(long long i=1;i<=n;i++)
			res[i][i]=1;
		while(x)
		{
			if(x&1)
				res=res*(*this);
			*this=(*this)*(*this);
			x>>=1;
		}
		return res;
	}
};

long long H,W,K;
char str[MAXN][MAXN];
long long lr,ud,v,ev,eh;

int main()
{
	scanf("%lld%lld%lld",&H,&W,&K);
	for(long long i=1;i<=H;i++)
		scanf("%s",str[i]+1);
	for(long long j=1;j<=W;j++)
		ud+=(str[1][j]=='#'&&str[H][j]=='#');
	for(long long i=1;i<=H;i++)
		lr+=(str[i][1]=='#'&&str[i][W]=='#');
	for(long long i=1;i<=H;i++)
		for(long long j=1;j<=W;j++)
			v+=(str[i][j]=='#');
	for(long long i=1;i<H;i++)
		for(long long j=1;j<=W;j++)
			ev+=(str[i][j]=='#'&&str[i+1][j]=='#');
	for(long long i=1;i<=H;i++)
		for(long long j=1;j<W;j++)
			eh+=(str[i][j]=='#'&&str[i][j+1]=='#');
	if(lr>0&&ud>0)
		puts("1");
	else if(lr==0&&ud==0)
		printf("%lld\n",PowMod(v,K-1));
	else if(lr>0&&ud==0)
	{
		swap(lr,ud);
		swap(ev,eh);
	}
	if(lr==0&&ud>0)
	{
		//printf("%lld %lld %lld\n",v,ev,ud);
		Matrix f;
		f.n=2;
		f[1][1]=v;
		f[1][2]=0;
		f[2][1]=ev;
		f[2][2]=ud;
		f=f.Pow(K-1);
		long long V=f[1][1],E=f[2][1];
		printf("%lld\n",((V-E)%MOD+MOD)%MOD);
	}
	
	return 0;
}
