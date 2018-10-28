#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXCHAR=26,MAXLOG=20;

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
            while(S[i+tmp]==S[sa[rk[i]+1]+tmp])
                tmp++;
            h[rk[i]]=tmp;
        }
    }
}

namespace STlist
{
    int mn[MAXN][MAXLOG];
    int lg[MAXN];

    void Init(const int A[],int n)
    {
        memset(mn,0x3F,sizeof mn);
        for(int i=1;i<=n;i++)
            mn[i][0]=A[i];
        for(int j=1;j<MAXLOG;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
        lg[1]=0;
        for(int i=2;i<=n;i++)
            lg[i]=lg[i/2]+1;
    }
    int RMQ(int L,int R)
    {return min(mn[L][lg[R-L+1]],mn[R-(1<<lg[R-L+1])+1][lg[R-L+1]]);}
}

int N,K;
char S[MAXN];

int sa[MAXN],rk[MAXN],h[MAXN];

void GetSubstr(long long rnk,int &a,int &b)
{
    long long r=0;
    for(int i=1;i<=N;i++)
    {
        if(r+N-sa[i]-h[i-1]+1>=rnk)
        {
            a=sa[i];
            b=sa[i]+h[i-1]+rnk-r-1;
            break;
        }
        r+=N-sa[i]-h[i-1]+1;
    }
}

bool check(long long ans)
{
    int a,b;
    GetSubstr(ans,a,b);

    int last=N+1,cnt=1;
    for(int i=N;i>=1;i--)
    {
        int lcp=min(b-a+1,last-i);
        if(rk[i]>rk[a])
            lcp=min(STlist::RMQ(rk[a],rk[i]-1),last);
        if(rk[i]<rk[a])
            lcp=min(STlist::RMQ(rk[i],rk[a]-1),last);
        char p=a+lcp>b?'\0':S[a+lcp],q=i+lcp>=last?'\0':S[i+lcp];
        if(p<q)
        {
            cnt++;
            last=i+1;
        }
    }
    return cnt<=K;
}

int main()
{
    scanf("%d%s",&K,S+1);
    N=strlen(S+1);
    SuffixArray::GetSa(S,sa,rk,h,N);
    STlist::Init(h,N);

    long long L=1,R=0;
    for(int i=1;i<=N;i++)
        R+=N-sa[i]-h[i-1]+1;
    while(L<R)
    {
        long long mid=(L+R)/2;
        if(check(mid))
            R=mid;
        else
            L=mid+1;
    }
    int a,b;
    GetSubstr(L,a,b);
    for(int i=a;i<=b;i++)
        putchar(S[i]);
    putchar('\n');

    return 0;
}
