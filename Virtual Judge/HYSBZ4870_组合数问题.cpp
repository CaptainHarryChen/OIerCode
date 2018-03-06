#include<cstdio>
const long long MAXN=53;

struct Matrix
{
	static long long MOD;
	long long h,w,a[MAXN][MAXN];
	Matrix(){h=w=0;}
	Matrix(long long h,long long w,long long *A=NULL):h(h),w(w)
	{
		for(long long i=0;i<h;i++)
			for(long long j=0;j<w;j++)
				a[i][j]=(A==NULL)?0:(*(A+(i*w)+h));
	}
	Matrix operator * (const Matrix &t)const
	{
		Matrix res(0,0,NULL);
		long long l=t.h;
		if(l!=this->w)
			return res;
		long long h=this->h;
		long long w=t.w;
		res=Matrix(h,w);
		for(long long i=0;i<h;i++)
			for(long long j=0;j<w;j++)
				for(long long k=0;k<l;k++)
					res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j]%MOD)%MOD;
		return res;
	}
	Matrix pow(long long b)const
	{
		Matrix res(0,0);
		if(h!=w)
			return res;
		Matrix d=*this;
		res=Matrix(h,w);
		for(long long i=0;i<h;i++)
			res.a[i][i]=1;
		while(b)
		{
			if(b&1)
				res=res*d;
			d=d*d;
			b>>=1;
		}
		return res;
	}
	void debug()
	{
		puts("---debug---");
		for(long long i=0;i<h;i++)
		{
			for(long long j=0;j<w;j++)
				printf("%lld ",a[i][j]);
			puts("");
		}
		puts("===debug===");
	}
};
long long Matrix::MOD;
int n,p,k,r;

Matrix A;
long long C[MAXN][MAXN];

int main()
{
	scanf("%d%d%d%d",&n,&p,&k,&r);
	Matrix::MOD=p;
	A.h=A.w=k;
	C[0][0]=1;
	for(long long i=1;i<=k;i++)
	{
		C[i][0]=C[i][i]=1;
		for(long long j=1;j<i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	for(long long i=0;i<k;i++)
		for(long long j=0;j<=k;j++)
			(A.a[i][(i+j)%k]+=C[k][j])%=p;
	//A.debug();
	A=A.pow(n);
	printf("%lld\n",A.a[0][r]);
	return 0;
}
