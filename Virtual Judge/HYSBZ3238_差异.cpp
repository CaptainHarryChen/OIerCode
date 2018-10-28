#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=500005,MAXCHAR=26;

namespace SuffixArray
{
    int sum[MAXN],tsa[MAXN],trk[MAXN];

    void GetSa(const char S[],int sa[],int rk[],int h[],int n)
    {
        memset(sum,0,sizeof sum);
        for(int i=1;i<=n;i++)
            sum[S[i]-'a']++;
        for(int c=1;c<MAXCHAR;c++)
            sum[c]+=sum[c-1];
        for(int i=n;i>0;i--)
            sa[sum[S[i]-'a']--]=i;
        for(int i=1;i<=n;i++)
            rk[sa[i]]=rk[sa[i-1]]+(S[sa[i]]!=S[sa[i-1]]);
        for(int len=1;rk[sa[n]]<n;len<<=1)
        {
            memset(sum,0,sizeof sum);
            for(int i=1;i<=n;i++)
                sum[i+len>n?0:rk[i+len]]++;
            for(int i=1;i<=n;i++)
                sum[i]+=sum[i-1];
            for(int i=n;i>0;i--)
                tsa[sum[i+len>n?0:rk[i+len]]--]=i;
            memset(sum,0,sizeof sum);
            for(int i=1;i<=n;i++)
                sum[rk[i]]++;
            for(int i=1;i<=n;i++)
                sum[i]+=sum[i-1];
            for(int i=n;i>0;i--)
                sa[sum[rk[tsa[i]]]--]=tsa[i];
            for(int i=1;i<=n;i++)
                trk[sa[i]]=trk[sa[i-1]]+(rk[sa[i]]!=rk[sa[i-1]]||(sa[i]+len>n?0:rk[sa[i]+len])!=(sa[i-1]+len>n?0:rk[sa[i-1]+len]));
            for(int i=1;i<=n;i++)
                rk[i]=trk[i];
        }
        for(int i=1;i<=n;i++)
        {
            int tmp=max(0,h[rk[i-1]]-1);
            while(S[i+tmp]==S[sa[rk[i]-1]+tmp])
                tmp++;
            h[rk[i]]=tmp;
        }
    }
}

int N;
char S[MAXN];

int sa[MAXN],rk[MAXN],h[MAXN];

int stk[MAXN],tp;
int L[MAXN],R[MAXN];

int main()
{
    scanf("%s",S+1);
    N=strlen(S+1);

    long long ans=0;
    for(int i=2;i<=N;i++)
        ans+=1LL*i*(i-1)/2*3;

    SuffixArray::GetSa(S,sa,rk,h,N);

    stk[tp=1]=1;
    for(int i=2;i<=N;i++)
    {
        while(tp>1&&h[stk[tp]]>h[i])
            tp--;
        L[i]=stk[tp];
        stk[++tp]=i;
    }
    stk[tp=1]=N;
    for(int i=N-1;i>=1;i--)
    {
        while(tp>1&&h[stk[tp]+1]>=h[i+1])
            tp--;
        R[i+1]=stk[tp];
        stk[++tp]=i;
    }

    for(int i=2;i<=N;i++)
        ans-=2LL*h[i]*(i-L[i])*(R[i]-i+1);

    printf("%lld\n",ans);

    return 0;
}
