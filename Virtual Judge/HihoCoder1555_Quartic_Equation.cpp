#include<cstdio>
#include<cstring>
const long long MOD=1000000007;

struct Matrix
{
	long long h,w;
	long long A[4][4];
	Matrix(){h=w=0;}
	Matrix(long long _h,long long _w)
	{
		h=_h;w=_w;
		for(long long i=0;i<h;i++)
			for(long long j=0;j<w;j++)
				A[i][j]=0;
	}
	Matrix(long long _h,long long _w,long long *buf)
	{
		h=_h;w=_w;
		for(long long i=0;i<h;i++)
			for(long long j=0;j<w;j++)
				A[i][j]=*(buf+i*w+j);
	}
	Matrix operator * (const Matrix &t)
	{
		if(w!=t.h)return Matrix();
		Matrix res(h,t.w);
		for(long long i=0;i<h;i++)
			for(long long j=0;j<t.w;j++)
				for(long long k=0;k<w;k++)
					res.A[i][j]=(res.A[i][j]+(1LL*A[i][k]*t.A[k][j])%MOD)%MOD;
		return res;
	}
	Matrix pow(long long n)
	{
		if(h!=w)return Matrix();
		Matrix res(h,w);
		for(long long i=0;i<4;i++)
			for(long long j=0;j<4;j++)
				res.A[i][j]=(i==j);
		while(n)
		{
			if(n&1LL)
				res=res*(*this);
			*this=(*this)*(*this);
			n>>=1LL;
		}
		return res;
	}
};

int main()
{
	long long n;
	long long T;
	long long a,b,c,d;
	scanf("%lld",&T);
	long long Af0[4][1];
	long long Adelta[4][4];
	Matrix f0,delta;
	while(T--)
	{
		scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
		memset(Af0,0,sizeof Af0);
		memset(Adelta,0,sizeof Adelta);
		Af0[0][0]=4;
		Af0[1][0]=(MOD-a)%MOD;
		Af0[2][0]=((1LL*a*a%MOD-2LL*b%MOD)%MOD+MOD)%MOD;
		Af0[3][0]=((-(1LL*a*a)%MOD*a%MOD+3LL*a*b%MOD-3LL*c%MOD)%MOD+MOD)%MOD;
		Adelta[0][1]=1;
		Adelta[1][2]=1;
		Adelta[2][3]=1;
		Adelta[3][0]=(MOD-d)%MOD;
		Adelta[3][1]=(MOD-c)%MOD;
		Adelta[3][2]=(MOD-b)%MOD;
		Adelta[3][3]=(MOD-a)%MOD;
		f0=Matrix(4,1,(long long*)Af0);
		delta=Matrix(4,4,(long long*)Adelta);
		if(n<4)
			printf("%lld\n",f0.A[n][0]);
		else
		{
			f0=delta.pow(n-3LL)*f0;
			printf("%lld\n",f0.A[3][0]);
		}
	}
}
