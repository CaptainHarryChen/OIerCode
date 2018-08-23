#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=200005;

int n,m,A[MAXN][2];
int f1[MAXN*4],f2[MAXN*4];

void PushUp(int id,int l,int mid,int r)
{
    int lch=id*2,rch=lch+1;
    if(f1[lch]==-1)
        f1[id]=-1;
    else
    {
        int tmp=A[mid][f1[lch]];
        if(A[mid+1][0]>=tmp)
            f1[id]=f1[rch];
        else if(A[mid+1][1]>=tmp)
            f1[id]=f2[rch];
        else
            f1[id]=-1;
    }
    if(f2[lch]==-1)
        f2[id]=-1;
    else
    {
        int tmp=A[mid][f2[lch]];
        if(A[mid+1][0]>=tmp)
            f2[id]=f1[rch];
        else if(A[mid+1][1]>=tmp)
            f2[id]=f2[rch];
        else
            f2[id]=-1;
    }
}

void Build(int l=1,int r=n,int id=1)
{
    if(l==r)
    {
        f1[id]=0;
        f2[id]=1;
        return;
    }
    int mid=(l+r)/2;
    Build(l,mid,id*2);
    Build(mid+1,r,id*2+1);
    PushUp(id,l,mid,r);
}
void Modify(int pos,int l=1,int r=n,int id=1)
{
    if(l==r)
    {
        f1[id]=0;
        f2[id]=1;
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        Modify(pos,l,mid,id*2);
    else
        Modify(pos,mid+1,r,id*2+1);
    PushUp(id,l,mid,r);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&A[i][0],&A[i][1]);
        if(A[i][0]>A[i][1])
            swap(A[i][0],A[i][1]);
    }
    Build();
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        int c,d;
        scanf("%d%d",&c,&d);
        if(c>d)
            swap(c,d);
        swap(A[c][0],A[d][0]);
        swap(A[c][1],A[d][1]);
        Modify(c);Modify(d);
        if(f1[1]!=-1)
            puts("TAK");
        else
            puts("NIE");
    }

    return 0;
}
