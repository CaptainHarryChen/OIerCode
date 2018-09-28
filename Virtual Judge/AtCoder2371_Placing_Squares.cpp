#include<cstdio>
#include<cstring>
const long long MOD=1000000007,MAXM=100005;

struct Matrix
{
	long long h,w;
	long long A[4][4];

    long long * operator [] (long long i)
    {return A[i];}
    const long long * operator [] (long long i) const
    {return A[i];}

	Matrix(){h=w=0;}
	Matrix(long long _h,long long _w)
	{
		h=_h;w=_w;
		for(long long i=0;i<h;i++)
			for(long long j=0;j<w;j++)
				A[i][j]=0;
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
	Matrix pow(long long n)const
	{
		if(h!=w)return Matrix();
		Matrix res(h,w);
		Matrix f=(*this);
		for(long long i=0;i<4;i++)
			for(long long j=0;j<4;j++)
				res.A[i][j]=(i==j);
		while(n)
		{
			if(n&1LL)
				res=res*f;
			f=f*f;
			n>>=1LL;
		}
		return res;
	}
};

/*
dp[0]=S[0]=T[0]=1;

dp[i]=dp[i-1]+S[i-1]+2*T[i-2];
 S[i]=dp[i]+S[i-1];
 T[i-1]=S[i-1]+T[i-2];

dp[i-1]     {1,1,2}   dp[i]
 S[i-1]  *  {1,2,2} =  S[i]
 T[i-2]     {0,1,1}    T[i-1]
*/

long long N,M,X[MAXM];
Matrix f,g;

int main()
{
    scanf("%lld%lld",&N,&M);
    for(long long i=1;i<=M;i++)
        scanf("%lld",&X[i]);

    f=Matrix(3,3);
    f[0][0]=1;f[0][1]=1;f[0][2]=2;
    f[1][0]=1;f[1][1]=2;f[1][2]=2;
    f[2][0]=0;f[2][1]=1;f[2][2]=1;

    long long dp=1,S=2,T=1,tdp,tS,tT;
    if(X[1]==1)
        S=1;
    X[0]=1;
    X[M+1]=N;
    for(long long i=1+(X[1]==1);i<=M+1;i++)
    {
        g=f.pow(X[i]-X[i-1]);
        tdp=(1LL*dp*g[0][0]%MOD+1LL*S*g[0][1]%MOD+1LL*T*g[0][2]%MOD)%MOD;
        tS=(1LL*dp*g[1][0]%MOD+1LL*S*g[1][1]%MOD+1LL*T*g[1][2]%MOD)%MOD;
        tT=(1LL*dp*g[2][0]%MOD+1LL*S*g[2][1]%MOD+1LL*T*g[2][2]%MOD)%MOD;
        dp=tdp;S=tS;T=tT;

        S=(S-dp+MOD)%MOD;
    }

    printf("%lld\n",dp);

    return 0;
}
