#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=300005,MOD=998244353,ROOT=3;

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
        while(j&k)
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
        int inv=PowMod(n,MOD-2);
        for(int i=0;i<n;i++)
            A[i]=1LL*A[i]*inv%MOD;
    }
}
void Multiply(const int A[],int n1,const int B[],int n2,int C[])
{
    static int tA[MAXN],tB[MAXN];
    int len=1;
    while(len<n1+n2-1)
        len<<=1;
    for(int i=0;i<n1;i++)tA[i]=A[i];
    for(int i=0;i<n2;i++)tB[i]=B[i];
    for(int i=n1;i<len;i++)tA[i]=0;
    for(int i=n2;i<len;i++)tB[i]=0;
    NTT(tA,len,1);
    NTT(tB,len,1);
    for(int i=0;i<len;i++)
        tA[i]=1LL*tA[i]*tB[i]%MOD;
    NTT(tA,len,-1);
    for(int i=0;i<n1+n2-1;i++)
        C[i]=tA[i];
}
void Inverse(const int A[],int n,int B[])
{
    static int tA[MAXN],tB[MAXN];
    if(n==1)
    {
        B[0]=PowMod(A[0],MOD-2);
        return;
    }
    Inverse(A,(n+1)/2,B);
    for(int i=(n+1)/2;i<n;i++)B[i]=0;
    for(int i=0;i<n;i++)tA[i]=A[i];
    for(int i=0;i<n;i++)tB[i]=B[i];
    int len=1;
    while(len<n+n-1)
        len<<=1;
    for(int i=n;i<len;i++)tA[i]=tB[i]=0;
    NTT(tA,len,1);NTT(tB,len,1);
    for(int i=0;i<len;i++)
        tA[i]=1LL*tB[i]*(2LL-1LL*tA[i]*tB[i]%MOD+MOD)%MOD;
    NTT(tA,len,-1);
    for(int i=0;i<n;i++)B[i]=tA[i];
}

int F[MAXN],G[MAXN],iG[MAXN];

int main()
{
    G[0]=1;
    for(int i=1;i<=100000;i++)
        G[i]=1LL*G[i-1]*i%MOD;
    Inverse(G,100001,iG);
    for(int i=0;i<=100000;i++)
        F[i]=(MOD-iG[i])%MOD;
    F[0]=(F[0]+1)%MOD;
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%d\n",F[n]);
    }
    return 0;
}
