#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=200005,MOD=1000000007;

int PowMod(int a,int b)
{
    int ret=1;
    while(b)
    {
        if(b&1)
            ret=1LL*ret*a%MOD;
        b>>=1;
        a=1LL*a*a%MOD;
    }
    return ret;
}

int n,X,Y;
int c[MAXN],w[MAXN];

vector<int> id[MAXN];
int mnid[MAXN];

vector<int> col[MAXN];
int cnt[MAXN];

int fac[MAXN],ifac[MAXN];

int fa[MAXN];
int Root(int x)
{return fa[x]==0?x:(fa[x]=Root(fa[x]));}
void Union(int x,int y)
{
    int r1=Root(x),r2=Root(y);
    if(r1==r2)
        return;
    fa[r1]=r2;
}

int main()
{
    scanf("%d%d%d",&n,&X,&Y);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&c[i],&w[i]);
        id[c[i]].push_back(i);
    }

    int mn,pos;
    for(int i=1;i<=n;i++)
    {
        mn=0x3F3F3F3F,pos=-1;
        for(int j=0;j<(int)id[i].size();j++)
            if(mn>w[id[i][j]])
                mn=w[id[i][j]],pos=id[i][j];
        for(int j=0;j<(int)id[i].size();j++)
            if(mn+w[id[i][j]]<=X)
                Union(pos,id[i][j]);
        mnid[i]=pos;
    }
    mn=0x3F3F3F3F,pos=-1;
    for(int i=1;i<=n;i++)
        if(mnid[i]!=-1&&mn>w[mnid[i]])
            mn=w[mnid[i]],pos=mnid[i];
    for(int i=1;i<=n;i++)
        if(mn+w[i]<=Y&&c[i]!=c[pos])
            Union(pos,i);
    int pos2=-1;
    mn=0x3F3F3F3F;
    for(int i=1;i<=n;i++)
        if(mnid[i]!=-1&&mn>w[mnid[i]]&&i!=c[pos])
            mn=w[mnid[i]],pos2=mnid[i];
    if(pos2!=-1)
        for(int i=1;i<=n;i++)
            if(mn+w[i]<=Y&&c[i]!=c[pos2])
                Union(pos2,i);
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1LL*fac[i-1]*i%MOD;
    ifac[n]=PowMod(fac[n],MOD-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=(1LL*ifac[i+1]*(i+1))%MOD;

    for(int i=1;i<=n;i++)
        col[Root(i)].push_back(c[i]);
    int ans=1;
    for(int i=1;i<=n;i++)
    {
        int all=0;
        for(int j=0;j<(int)col[i].size();j++)
            cnt[col[i][j]]++,all++;
        ans=1LL*ans*fac[all]%MOD;
        for(int j=0;j<(int)col[i].size();j++)
        {
            ans=1LL*ans*ifac[cnt[col[i][j]]]%MOD;
            cnt[col[i][j]]=0;
        }
    }
    printf("%d\n",ans);

    return 0;
}
