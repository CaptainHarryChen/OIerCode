//CodeChef RNG
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXK=30005,MOD=104857601,ROOT=3;
typedef int Poly[MAXK*6];

int PowMod(int a,int b)
{
    int res=1;
    for(;b;b>>=1,a=1LL*a*a%MOD)
        if(b&1)
            res=1LL*res*a%MOD;
    return res;
}

void NTT(Poly &A,int n,int mode)
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

void Multiply(const Poly &A,int len1,const Poly &B,int len2,Poly &C)
{
    static Poly A0,B0;
    int len=1;
    while(len<len1+len2-1)len<<=1;
    for(int i=0;i<len1;i++)A0[i]=A[i];
    for(int i=0;i<len2;i++)B0[i]=B[i];
    for(int i=len1;i<len;i++)A0[i]=0;
    for(int i=len2;i<len;i++)B0[i]=0;
    NTT(A0,len,1);NTT(B0,len,1);
    for(int i=0;i<len;i++)A0[i]=1LL*A0[i]*B0[i]%MOD;
    NTT(A0,len,-1);
    for(int i=0;i<len1+len2-1;i++)C[i]=A0[i];
}
void Inverse(const Poly &A,Poly &B,int deg)
{
    if(deg==1)
    {
        B[0]=PowMod(A[0],MOD-2);
        B[1]=0;
        return;
    }
    static Poly A0;
    Inverse(A,B,(deg+1)/2);
    int len=1;
    while(len<deg*2-1)len<<=1;
    for(int i=0;i<deg;i++)A0[i]=A[i];
    for(int i=deg;i<len;i++)A0[i]=B[i]=0;
    NTT(A0,len,1);NTT(B,len,1);
    for(int i=0;i<len;i++)
        B[i]=1LL*B[i]*((2LL-1LL*B[i]*A0[i]%MOD+MOD)%MOD)%MOD;
    NTT(B,len,-1);
    for(int i=deg;i<len;i++)B[i]=0;
}
void Module(Poly &A,int len1,const Poly &B,int len2)
{
    static Poly B0,iB0,C;
    for(int i=0;i<len2;i++)B0[i]=B[i];
    reverse(A,A+len1);
    reverse(B0,B0+len2);
    Inverse(B0,iB0,len1-len2+1);
    Multiply(A,len1,iB0,len1-len2+1,C);
    for(int i=len1-len2+1;i<2*len1-len2;i++)C[i]=0;
    reverse(C,C+len1-len2+1);
    reverse(A,A+len1);
    Multiply(B,len2,C,len1-len2+1,C);
    for(int i=0;i<len1;i++)A[i]=(A[i]-C[i]+MOD)%MOD;
}
void PowMod(Poly &A,int len1,long long b,const Poly &P,int len2)
{
    static Poly res;
    res[0]=1;
    for(int i=1;i<len2;i++)res[i]=0;
    for(int i=len1;i<len2;i++)A[i]=0;
    for(;b;b>>=1)
    {
        if(b&1)
        {
            Multiply(res,len2,A,len2,res);
            Module(res,len2*2-1,P,len2);
        }
        Multiply(A,len2,A,len2,A);
        Module(A,len2*2-1,P,len2);
    }
    for(int i=0;i<len2;i++)A[i]=res[i];
}

long long N;
int K,A[MAXK],C[MAXK];

Poly f,P;

int main()
{
    scanf("%d%lld",&K,&N);
    for(int i=1;i<=K;i++)
        scanf("%d",&A[i]);
    for(int i=1;i<=K;i++)
        scanf("%d",&C[i]);

    for(int i=0;i<K;i++)
        P[i]=(MOD-C[K-i])%MOD;
    P[K]=1;
    f[1]=1;
    PowMod(f,2,N-1,P,K+1);
    int ans=0;
    for(int i=0;i<K;i++)
        ans=(ans+1LL*f[i]*A[i+1]%MOD)%MOD;
    printf("%d\n",ans);

    return 0;
}
