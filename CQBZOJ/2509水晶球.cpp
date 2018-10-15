#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;

int M,N;
int A[MAXN*2];
int l[MAXN],r[MAXN],p[MAXN];

int fa[MAXN*2],val[MAXN*2];
int Root(int u)
{
    if(fa[u]==u)
        return u;
    int rt=Root(fa[u]);
    val[u]=val[fa[u]]+val[u];
    fa[u]=rt;
    return rt;
}

int main()
{
    scanf("%d",&M);
    for(int i=1;i<=M;i++)
    {
        scanf("%d%d%d",&l[i],&r[i],&p[i]);
        l[i]--;
        A[i*2-1]=l[i];
        A[i*2]=r[i];
    }

    sort(A+1,A+M*2+1);
    N=unique(A+1,A+M*2+1)-A-1;
    for(int i=1;i<=M;i++)
    {
        l[i]=lower_bound(A+1,A+N+1,l[i])-A;
        r[i]=lower_bound(A+1,A+N+1,r[i])-A;
    }

    for(int i=1;i<=N;i++)
    {
        fa[i]=i;
        val[i]=0;
    }
    for(int i=1;i<=M;i++)
    {
        int r1=Root(l[i]),r2=Root(r[i]);
        if(r1==r2)
        {
            if(val[l[i]]-val[r[i]]==p[i])
                puts("Accept");
            else
                printf("Bug Detected %d\n",val[l[i]]-val[r[i]]);
        }
        else
        {
            fa[r1]=r2;
            val[r1]=val[r[i]]+p[i]-val[l[i]];
            puts("Accept");
        }
    }

    return 0;
}
