#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=100005,MAXM=1000005,BLKSIZ=317,BLKNUM=MAXN/BLKSIZ+5;

void Read(int &x)
{
    char c;
    while(c=getchar(),c!=EOF)
    {
        if(c>='0'&&c<='9')
        {
            x=c-'0';
            while(c=getchar(),c>='0'&&c<='9')
                x=x*10+c-'0';
            return;
        }
    }
}
void Print(int x)
{
    if(x==0)
        putchar('0');
    else
    {
        char s[20];
        int tp=0;
        while(x)
            s[tp++]=x%10+'0',x/=10;
        while(tp--)
            putchar(s[tp]);
    }
}

struct Query
{
    int l,r,a,b,id;
};

bool cmp(const Query &a,const Query &b)
{
    if(a.l/100==b.l/100)
        return a.r<b.r;
    return a.l/100<b.l/100;
}

int n,m,A[MAXN];

Query Q[MAXM];
int ans[MAXM];

int cntA[MAXN],cntB[BLKNUM];
void Add(int p)
{
    if(cntA[A[p]]==0)
        cntB[A[p]/BLKSIZ]++;
    cntA[A[p]]++;
}
void Del(int p)
{
    cntA[A[p]]--;
    if(cntA[A[p]]==0)
        cntB[A[p]/BLKSIZ]--;
}
int Count(int a,int b)
{
    int res=0;
    if(a/BLKSIZ==b/BLKSIZ)
    {
        for(int i=a;i<=b;i++)
            res+=cntA[i]!=0;
        return res;
    }
    for(int i=a;i/BLKSIZ==a/BLKSIZ;i++)
        res+=cntA[i]!=0;
    for(int i=b;i/BLKSIZ==b/BLKSIZ;i--)
        res+=cntA[i]!=0;
    for(int j=a/BLKSIZ+1;j<b/BLKSIZ;j++)
        res+=cntB[j];
    return res;
}

int main()
{
    Read(n);Read(m);
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]);
    for(int i=1;i<=m;i++)
    {
        Read(Q[i].l);Read(Q[i].r);Read(Q[i].a);Read(Q[i].b);
        Q[i].id=i;
    }
    sort(Q+1,Q+m+1,cmp);

    int L=1,R=0;
    for(int i=1;i<=m;i++)
    {
        while(R<Q[i].r)
            R++,Add(R);
        while(L>Q[i].l)
            L--,Add(L);
        while(R>Q[i].r)
            Del(R),R--;
        while(L<Q[i].l)
            Del(L),L++;
        ans[Q[i].id]=Count(Q[i].a,Q[i].b);
    }

    for(int i=1;i<=m;i++)
    {
        Print(ans[i]);
        putchar('\n');
    }

    return 0;
}
