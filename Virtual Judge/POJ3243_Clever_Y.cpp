#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;

namespace Hash
{
    const int HASHSIZE=31643,MAXNODE=31650;
    struct Node
    {
        int id,val;
        Node *nxt;
    }nd[MAXNODE],*hd[HASHSIZE],*nd_it;
    void Clear()
    {
        memset(hd,0,sizeof hd);
        nd_it=nd;
    }
    void Add(int pos,int val)
    {
        int x=pos%HASHSIZE;
        nd_it->id=pos;
        nd_it->val=val;
        nd_it->nxt=hd[x];
        hd[x]=nd_it++;
    }
    int Get(int pos)
    {
        for(Node *u=hd[pos%HASHSIZE];u;u=u->nxt)
            if(u->id==pos)
                return u->val;
        return -1;
    }
}

int PowMod(int a,int b,int p)
{
    int res=1;
    for(;b;b>>=1,a=1LL*a*a%p)
        if(b&1)
            res=1LL*res*a%p;
    return res;
}
int gcd(int a,int b)
{return b==0?a:gcd(b,a%b);}
void exgcd(int a,int b,int &x,int &y)
{
    if(b==0)
    {
        x=1;y=0;
        return;
    }
    exgcd(b,a%b,y,x);
    y-=(a/b)*x;
}
int inv(int a,int p)
{
    int i,k;
    exgcd(a,p,i,k);
    i=(i%p+p)%p;
    return i;
}

int exBSGS(int A,int B,int P)
{
    if(B==1)
        return 0;
    int res=0,a2=1,d;
    for(;;)
    {
        d=gcd(A,P);
        if(d==1)
            break;
        if(B%d!=0)
            return -1;
        res++;
        a2=(1LL*A/d*a2)%P;
        B/=d;P/=d;
        if(a2==B)
            return res;
    }
    B=1LL*B*inv(a2,P)%P;
    Hash::Clear();
    int tmp=1,m=ceil(sqrt(P)),a3;
    for(int j=0;j<m;j++)
    {
        Hash::Add(tmp,j);
        tmp=1LL*tmp*A%P;
    }
    a3=inv(PowMod(A,m,P),P);
    tmp=B;
    for(int j=0;j<m;j++)
    {
        int v=Hash::Get(tmp);
        if(v!=-1)
            return j*m+v+res;
        tmp=1LL*tmp*a3%P;
    }
    return -1;
}

int main()
{
    int X,Z,K;
    for(;;)
    {
        scanf("%d%d%d",&X,&Z,&K);
        if(X==0&&Z==0&&K==0)
            break;
        int res=exBSGS(X,K,Z);
        if(res==-1)
            puts("No Solution");
        else
            printf("%d\n",res);
    }
    return 0;
}
