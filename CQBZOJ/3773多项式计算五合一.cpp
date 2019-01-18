#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXLOG=20,MOD=998244353,ROOT=3;

int PowMod(int a,int b)
{
    int res=1;
    for(;b;b>>=1,a=1LL*a*a%MOD)
        if(b&1)
            res=1LL*res*a%MOD;
    return res;
}
void NTT(int A[],int n,int mode)
{
    for(int i=0,j=0;i<n;i++)
    {
        if(i<j)
            swap(A[i],A[j]);
        int k=n>>1;
        while(k&j)
            j^=k,k>>=1;
        j^=k;
    }
    for(int i=1;i<n;i<<=1)
    {
        int w1=PowMod(ROOT,(MOD-1)/(i<<1));
        if(mode==-1)
            w1=PowMod(w1,MOD-2);
        for(int j=0;j<n;j+=(i<<1))
            for(int l=j,r=j+i,w=1;l<j+i;l++,r++,w=1LL*w*w1%MOD)
            {
                int tmp=1LL*A[r]*w%MOD;
                A[r]=(A[l]-tmp+MOD)%MOD;
                A[l]=(A[l]+tmp)%MOD;
            }
    }
    if(mode==-1)
    {
        int invn=PowMod(n,MOD-2);
        for(int i=0;i<n;i++)
            A[i]=1LL*A[i]*invn%MOD;
    }
}

void Multiply(const int A[],int len1,const int B[],int len2,int C[])
{
    static int A0[MAXN*3],B0[MAXN*3];
    int len=1;
    for(;len<len1+len2-1;len<<=1);
    for(int i=0;i<len1;i++)A0[i]=A[i];
    for(int i=len1;i<len;i++)A0[i]=0;
    for(int i=0;i<len2;i++)B0[i]=B[i];
    for(int i=len2;i<len;i++)B0[i]=0;
    NTT(A0,len,1);NTT(B0,len,1);
    for(int i=0;i<len;i++)A0[i]=1LL*A0[i]*B0[i]%MOD;
    NTT(A0,len,-1);
    for(int i=0;i<len1+len2-1;i++)C[i]=A0[i];
}
void Inverse(const int A[],int B[],int n)
{
    if(n==1)
    {
        B[0]=PowMod(A[0],MOD-2);B[1]=0;
        return;
    }
    static int A0[MAXN*3];
    Inverse(A,B,(n+1)/2);
    int len=1;
    for(;len<n*2-1;len<<=1);
    for(int i=0;i<n;i++)A0[i]=A[i];
    for(int i=n;i<len;i++)A0[i]=B[i]=0;
    NTT(A0,len,1);NTT(B,len,1);
    for(int i=0;i<len;i++)
        B[i]=1LL*B[i]*((2LL-1LL*B[i]*A0[i]%MOD+MOD)%MOD)%MOD;
    NTT(B,len,-1);
    for(int i=n;i<n*2-1;i++)B[i]=0;
}

void Module(int A[],int len1,const int B[],int len2)
{
    static int A0[MAXN*3],B0[MAXN*3],iB0[MAXN*3],C[MAXN*3];
    if(len1<len2)return;
    for(int i=0;i<len1;i++)A0[i]=A[len1-i-1];
    for(int i=0;i<len2;i++)B0[i]=B[len2-i-1];
    Inverse(B0,iB0,len1-len2+1);
    Multiply(A0,len1,iB0,len1-len2+1,C);
    for(int i=len1-len2+1;i<2*len1-len2;i++)C[i]=0;
    reverse(C,C+len1-len2+1);
    Multiply(C,len1-len2+1,B,len2,C);
    for(int i=0;i<len1;i++)A[i]=(A[i]-C[i]+MOD)%MOD;
}
void Derivation(const int A[],int B[],int n)
{
	for(int i=1;i<n;i++)
		B[i-1]=1LL*A[i]*i%MOD;
	B[n-1]=0;
}
void Integral(const int A[],int B[],int n)
{
	for(int i=n;i>=1;i--)
		B[i]=1LL*A[i-1]*PowMod(i,MOD-2)%MOD;
	B[0]=0;
}
void Logarithm(const int A[],int B[],int n)//需保证A[0]=1
{
    static int iA[MAXN*3],A1[MAXN*3];
    Inverse(A,iA,n);
    Derivation(A,A1,n);
    Multiply(A1,n-1,iA,n,A1);
    Integral(A1,B,n);
}
void Exponential(const int A[],int B[],int n)//需保证A[0]=0;
{
    if(n==1)
    {
        B[0]=1;
        return;
    }
    Exponential(A,B,(n+1)/2);
    static int A0[MAXN*3];
    Logarithm(B,A0,n);
    for(int i=0;i<n;i++)A0[i]=(MOD-A0[i]+A[i])%MOD;
    A0[0]=(A0[0]+1)%MOD;
    Multiply(B,n,A0,n,B);
    for(int i=n;i<n*2;i++)B[i]=0;
}
void Power(const int A[],int B[],int n,int k)
{
	static int A0[MAXN*3];
	for(int i=0;i<n;i++)A0[i]=0;
	Logarithm(A,A0,n);
	for(int i=0;i<n;i++)A0[i]=1LL*A0[i]*k%MOD;
	Exponential(A0,B,n);
}
void Sqrt(const int A[],int B[],int n)
{
	if(n==1)
	{
		B[0]=sqrt(A[0]);
		return;
	}
	Sqrt(A,B,(n+1)/2);
	static int A0[MAXN*3],B0[MAXN*3],iB0[MAXN*3];
	for(int i=0;i<n;i++)B0[i]=2LL*B[i]%MOD;
	Inverse(B0,iB0,n);
	Multiply(B,n,B,n,A0);
	for(int i=n;i<n*2;i++)A0[i]=0;
	for(int i=0;i<n;i++)A0[i]=(A[i]+A0[i])%MOD;
	Multiply(iB0,n,A0,n,B);
	for(int i=n;i<n*2;i++)B[i]=0;
}

int N,K,A[MAXN*3],B[MAXN*3];
void Swap()
{
	for(int i=0;i<N+1;i++)
		A[i]=B[i],B[i]=0;
}

int main()
{
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;i++)
		scanf("%d",&A[i]);
	Sqrt(A,B,N);Swap();
	Inverse(A,B,N);Swap();
	Integral(A,B,N);Swap();
	Exponential(A,B,N+1);Swap();
	Inverse(A,B,N+1);
	B[0]=(B[0]+1)%MOD;Swap();
	Logarithm(A,B,N+1);
	B[0]=(B[0]+1)%MOD;Swap();
	Power(A,B,N+1,K);Swap();
	Derivation(A,B,N);Swap();
	for(int i=0;i<N-1;i++)
		printf("%d ",A[i]);
	printf("%d",A[N-1]);

    return 0;
}
