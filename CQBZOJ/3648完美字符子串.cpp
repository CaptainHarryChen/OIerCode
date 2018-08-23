#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
const int MAXN=1000005;

int n;
int L[MAXN],R[MAXN],sum[MAXN];
int A[MAXN];
int stk[MAXN],top;
char str[MAXN];

int mx[MAXN*4];
void Build(int l=0,int r=n,int id=1)
{
    if(l==r)
    {
        mx[id]=R[l];
        return;
    }
    int mid=(l+r)/2;
    Build(l,mid,id*2);
    Build(mid+1,r,id*2+1);
    mx[id]=max(mx[id*2],mx[id*2+1]);
}
int Query(int ql,int qr,int qval,int l=0,int r=n,int id=1)
{
    if(mx[id]<qval||r<ql||qr<l)
        return 0x3F3F3F3F;
    if(l==r)
        return l;
    int mid=(l+r)/2;
    if(qr<=mid)
        return Query(ql,qr,qval,l,mid,id*2);
    else if(ql>mid)
        return Query(ql,qr,qval,mid+1,r,id*2+1);
    return min(Query(ql,qr,qval,l,mid,id*2),Query(ql,qr,qval,mid+1,r,id*2+1));
}

int main()
{
    scanf("%d%s",&n,str);
    for(int i=1;i<=n;i++)
    {
        A[i]=(str[i-1]=='p'?1:-1);
        sum[i]=sum[i-1]+A[i];
    }
    sum[n+1]=-0x3F3F3F3F;

    stk[0]=-1;
    stk[top=1]=0;
    for(int i=1;i<=n;i++)
    {
        while(top&&sum[stk[top]]<=sum[i])
            top--;
        L[i]=stk[top]+1;
        stk[++top]=i;
    }
    stk[0]=n+1;
    stk[top=1]=n+1;
    for(int i=n;i>=0;i--)
    {
        while(top&&sum[stk[top]]>=sum[i])
            top--;
        R[i]=stk[top]-1;
        stk[++top]=i;
    }

    Build();
    int ans=0;
    for(int i=n;i>=1;i--)
        if(i-L[i]>ans)
        {
            ans=max(ans,i-Query(L[i],i-1,i));
            //fprintf(stderr,"*");
        }
    printf("%d\n",ans);

    return 0;
}
