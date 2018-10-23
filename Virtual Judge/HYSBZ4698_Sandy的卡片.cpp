#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXM=1000005;

int n,m;
int A[MAXM],s[MAXM],pos[MAXM];
int val[MAXM],valc;

int sa[MAXM],h[MAXM],rk[MAXM];
int sum[MAXM],a[MAXM],b[MAXM],tsa[MAXM];

void GetSA()
{
    for(int i=1;i<=m;i++)
        sum[s[i]]++;
    for(int i=1;i<MAXM;i++)
        sum[i]+=sum[i-1];
    for(int i=m;i>=1;i--)
        sa[sum[s[i]]--]=i;
    for(int i=1;i<=m;i++)
        rk[sa[i]]=rk[sa[i-1]]+(s[sa[i-1]]!=s[sa[i]]);
    for(int len=1;rk[sa[m]]<m;len<<=1)
    {
        for(int i=1;i<=m;i++)
        {
            a[i]=rk[i];
            b[i]=i+len<=m?rk[i+len]:0;
        }
        memset(sum,0,sizeof sum);
        for(int i=1;i<=m;i++)
            sum[b[i]]++;
        for(int i=1;i<=m;i++)
            sum[i]+=sum[i-1];
        for(int i=m;i>=1;i--)
            tsa[sum[b[i]]--]=i;
        memset(sum,0,sizeof sum);
        for(int i=1;i<=m;i++)
            sum[a[i]]++;
        for(int i=1;i<=m;i++)
            sum[i]+=sum[i-1];
        for(int i=m;i>=1;i--)
            sa[sum[a[tsa[i]]]--]=tsa[i];
        for(int i=1;i<=m;i++)
            rk[sa[i]]=rk[sa[i-1]]+(a[sa[i-1]]!=a[sa[i]]||b[sa[i-1]]!=b[sa[i]]);
    }
    for(int i=1,k=0;i<m;i++)
    {
        k=max(0,h[rk[i-1]]-1);
        while(s[i+k]==s[sa[rk[i]+1]+k])
            k++;
        h[rk[i]]=k;
    }
}

bool vis[1005];

bool check(int mid)
{
    memset(vis,0,sizeof vis);
    int cnt=0;
    for(int i=1;i<=m;i++)
        if(h[i]<mid)
        {
            memset(vis,0,sizeof vis);
            cnt=0;
        }
        else
        {
            if(!vis[pos[sa[i]]])
                cnt++,vis[pos[sa[i]]]=true;
            if(!vis[pos[sa[i+1]]])
                cnt++,vis[pos[sa[i+1]]]=true;
            if(cnt>=n)
                return true;
        }
    return false;
}

int main()
{
    scanf("%d",&n);
    int tmp=-10000000;
    for(int i=1;i<=n;i++)
    {
        int k;
        scanf("%d",&k);
        for(int j=1;j<=k;j++)
        {
            scanf("%d",&A[j]);
            if(j!=1)
                s[++m]=A[j]-A[j-1];
            pos[m]=i;
        }
        s[++m]=tmp--;
    }

    memcpy(val,s,sizeof val);
    sort(val+1,val+m+1);
    valc=unique(val+1,val+m+1)-val-1;
    for(int i=1;i<=m;i++)
        s[i]=lower_bound(val+1,val+valc+1,s[i])-val;

    GetSA();
    int L=1,R=1000;
    while(L<R)
    {
        int mid=(L+R+1)/2;
        if(check(mid))
            L=mid;
        else
            R=mid-1;
    }
    printf("%d\n",L+1);

    return 0;
}
