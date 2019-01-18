//luogu 5050
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=64005,MAXLOG=18,MOD=998244353,ROOT=3;

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
        if(i<j)swap(A[i],A[j]);
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
    for(int i=0;i<len;i++)
        A0[i]=1LL*A0[i]*B0[i]%MOD;
    NTT(A0,len,-1);
    for(int i=0;i<len1+len2-1;i++)C[i]=A0[i];
}

int main()
{
	
	return 0;
}
