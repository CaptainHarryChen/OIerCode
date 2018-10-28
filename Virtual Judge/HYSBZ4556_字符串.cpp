#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXCHAR=26;

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

int n,m;
char S[MAXN];

int sa[MAXN],rk[MAXN],h[MAXN];

int main()
{
    scanf("%d%d%s",&n,&m,S+1);
    SuffixArray::GetSa(S,sa,rk,h,n);

    for(int i=1;i<=m;i++)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int ans=0,len=0x3F3F3F3F;
        if(sa[rk[c]]>=a&&sa[rk[c]]<=b)
            ans=max(ans,min(b-sa[rk[c]]+1,d-c+1));
        for(int j=rk[c]-1;j>0;j--)
        {
            if(h[j]==0||h[j]<=ans)
                break;
            len=min(len,h[j]);
            if(sa[j]>=a&&sa[j]<=b)
                ans=max(ans,min(len,min(b-sa[j]+1,d-c+1)));
        }
        len=0x3F3F3F3F;
        for(int j=rk[c];j<n;j++)
        {
            if(h[j]==0||h[j]<=ans)
                break;
            len=min(len,h[j]);
            if(sa[j+1]>=a&&sa[j+1]<=b)
                ans=max(ans,min(len,min(b-sa[j+1]+1,d-c+1)));
        }
        printf("%d\n",ans);
    }

    return 0;
}
