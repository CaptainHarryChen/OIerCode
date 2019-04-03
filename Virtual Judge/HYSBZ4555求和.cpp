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
int SumPowMod(int a,int b)
{
    int x=1,y=a,s=1,res=0;
    for(;b;b>>=1)
    {
        if(b&1)
        {
            res=(res+1LL*s*x%MOD)%MOD;
            x=1LL*x*y%MOD;
        }
        s=(s+1LL*s*y%MOD)%MOD;
        y=1LL*y*y%MOD;
    }
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
        {
            int w=1;
            for(int l=j,r=j+i;l<j+i;l++,r++,w=1LL*w*w1%MOD)
            {
                int tmp=1LL*A[r]*w%MOD;
                A[r]=(A[l]-tmp+MOD)%MOD;
                A[l]=(A[l]+tmp)%MOD;
            }
        }
    }
    if(mode==-1)
    {
        int inv=PowMod(n,MOD-2);
        for(int i=0;i<n;i++)
            A[i]=1LL*A[i]*inv%MOD;
    }
}

int fac[MAXN],ifac[MAXN];
int A[MAXN],B[MAXN];

int main()
{
    int n,len;
    scanf("%d",&n);
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1LL*fac[i-1]*i%MOD;
    ifac[n]=PowMod(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1LL*ifac[i+1]*(i+1)%MOD;
    for(int i=0;i<=n;i++)
        A[i]=(((i&1)?-1:1)*ifac[i]+MOD)%MOD;
    for(int i=0;i<=n;i++)
        B[i]=1LL*SumPowMod(i,n+1)*ifac[i]%MOD;
    for(len=1;len<n*2+1;len<<=1);
    NTT(A,len,1);
    NTT(B,len,1);
    for(int i=0;i<len;i++)
        A[i]=1LL*A[i]*B[i]%MOD;
    NTT(A,len,-1);
    int pow2=1,ans=0;
    for(int i=0;i<=n;i++,pow2=2LL*pow2%MOD)
        ans=(ans+1LL*pow2*fac[i]%MOD*A[i]%MOD)%MOD;
    printf("%d\n",ans);

    return 0;
}
