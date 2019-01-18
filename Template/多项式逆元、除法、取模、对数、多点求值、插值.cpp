#include<cstdio>
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
int W[2][MAXLOG][MAXN*6],iW[MAXLOG][MAXN*6];
void InitNTT()
{
    for(int i=0;(1<<i)<MAXN*6;i++)
    {
        W[0][i][0]=W[1][i][0]=1;
        W[0][i][1]=PowMod(ROOT,(MOD-1)/(1<<i));
        W[1][i][1]=PowMod(W[0][i][1],MOD-2);
        for(int j=2;j<(1<<i);j++)
        {
            W[0][i][j]=1LL*W[0][i][j-1]*W[0][i][1]%MOD;
            W[1][i][j]=1LL*W[1][i][j-1]*W[1][i][1]%MOD;
        }
    }
}
void NTT(int A[],int n,int mode)
{
    for(int i=0,j=0;i<n;i++)
    {
        if(i<j)swap(A[i],A[j]);
        int k=n>>1;
        while(k&j)
            j^=k,k>>=1;
        j^=k;
    }
    mode=mode==1?0:1;
    for(int i=1,c=1;i<n;i<<=1,c++)
        for(int j=0;j<n;j+=(i<<1))
            for(int l=j,r=j+i;l<j+i;l++,r++)
            {
                int tmp=1LL*A[r]*W[mode][c][l-j]%MOD;
                A[r]=(A[l]-tmp+MOD)%MOD;
                A[l]=(A[l]+tmp)%MOD;
            }
    if(mode==1)
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
    for(int i=0;i<len;i++)
        A0[i]=1LL*A0[i]*B0[i]%MOD;
    NTT(A0,len,-1);
    for(int i=0;i<len1+len2-1;i++)C[i]=A0[i];
}

void Inverse(const int A[],int B[],int deg)
{
    if(deg==1)
    {
        B[0]=PowMod(A[0],MOD-2);
        B[1]=0;
        return;
    }
    static int A0[MAXN];
    Inverse(A,B,(deg+1)/2);
    int len=1;
    for(;len<deg*2-1;len<<=1);
    for(int i=0;i<deg;i++)A0[i]=A[i];
    for(int i=deg;i<len;i++)A0[i]=B[i]=0;
    NTT(A0,len,1);NTT(B,len,1);
    for(int i=0;i<len;i++)
        B[i]=1LL*B[i]*((2LL-1LL*A0[i]*B[i]%MOD+MOD)%MOD)%MOD;
    NTT(B,len,-1);
    for(int i=deg;i<len;i++)B[i]=0;
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
	for(int i=0;i<n;i++)iA[i]=A1[i]=0;
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

int *P[MAXN*4],buf[MAXN*MAXLOG*6],*bufit=buf;
int dP[MAXN],Pi[MAXN];

void CalcP(int i,int X[],int L,int R)
{
    if(L==R)
    {
        P[i]=bufit;bufit+=2;
        P[i][1]=1;P[i][0]=(MOD-X[L])%MOD;
        return;
    }
    int mid=(L+R)/2;
    CalcP(i*2,X,L,mid);
    CalcP(i*2+1,X,mid+1,R);
    P[i]=bufit;bufit+=(R-L+2);
    Multiply(P[i*2],mid-L+2,P[i*2+1],R-mid+1,P[i]);
}
void Evaluation(const int A[],int len1,int i,int L,int R,int ans[])
{
    int *A0=bufit;bufit+=len1;
    for(int i=0;i<len1;i++)A0[i]=A[i];
    Module(A0,len1,P[i],R-L+2);
    if(L==R)
    {
        ans[L]=A0[0];
        return;
    }
    int mid=(L+R)/2;
    Evaluation(A0,min(R-L+1,len1),i*2,L,mid,ans);
    Evaluation(A0,min(R-L+1,len1),i*2+1,mid+1,R,ans);
}
void Interpolate(const int X[],const int Y[],int i,int L,int R,int A[])
{
    if(L==R)
    {
        A[0]=1LL*Y[L]*PowMod(Pi[L],MOD-2)%MOD;
        return;
    }
    static int res1[MAXN],res2[MAXN];
    int mid=(L+R)/2,len1=mid-L+1,len2=R-mid;
    Interpolate(X,Y,i*2,L,mid,A);
    Interpolate(X,Y,i*2+1,mid+1,R,A+len1);
    Multiply(A,len1,P[i*2+1],len2+1,res1);
    Multiply(A+len1,len2,P[i*2],len1+1,res2);
    for(int i=0;i<R-L+1;i++)A[i]=(res1[i]+res2[i])%MOD;
}

int N;
int A[MAXN],X[MAXN],Y[MAXN];

int main()
{
    return 0;
}
