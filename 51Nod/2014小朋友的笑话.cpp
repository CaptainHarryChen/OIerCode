#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
const int MAXN=100005;
typedef set<pair<int,int>>::iterator iter;

int N,M;
set<pair<int,int>> seg[MAXN];

int cnt[MAXN*4],mk[MAXN*4];

void PushDown(int L,int R,int u)
{
    if(mk[u]!=0)
    {
        mk[u*2]=mk[u*2+1]=mk[u];
        if(mk[u]==-1)
            cnt[u*2]=cnt[u*2+1]=0;
        else if(mk[u]==1)
            cnt[u*2]=(L+R)/2-L+1,cnt[u*2+1]=R-(L+R)/2;
    }
}
void PushUp(int u)
{
    cnt[u]=cnt[u*2]+cnt[u*2+1];
    if(mk[u*2]==0||mk[u*2+1]==0||mk[u*2]!=mk[u*2+1])
        mk[u]=0;
    else
        mk[u]=mk[u*2];
}
void Mark(int l,int r,int mode,int L=1,int R=N,int u=1)
{
    if(l<=L&&R<=r)
    {
        mk[u]=mode;
        cnt[u]=mode==1?R-L+1:0;
        return;
    }
    PushDown(L,R,u);
    int mid=(L+R)/2;
    if(l<=mid)
        Mark(l,r,mode,L,mid,u*2);
    if(mid<r)
        Mark(l,r,mode,mid+1,R,u*2+1);
    PushUp(u);
}
int Query(int l,int r,int L=1,int R=N,int u=1)
{
    if(l<=L&&R<=r)
        return cnt[u];
    PushDown(L,R,u);
    int mid=(L+R)/2,res=0;
    if(l<=mid)
        res+=Query(l,r,L,mid,u*2);
    if(mid<r)
        res+=Query(l,r,mid+1,R,u*2+1);
    return res;
}
void Add(int id,int l,int r)
{
    int L=l,R=r,last=l-1;
    iter i=seg[id].lower_bound(make_pair(l,0));
    if(i!=seg[id].begin())
        i--;
    if(i==seg[id].end())
    {
        Mark(l,r,1);
        seg[id].insert(make_pair(l,r));
        return;
    }
    if(i->first<l&&i->second>=l)
    {
        if(i->second>=r)
        {
            Mark(l,r,-1);
            return;
        }
        Mark(l,i->second,-1);
        L=i->first;
        last=i->second;
        i=seg[id].erase(i);
    }
    else if(i->first<l)
        i++;
    while(i!=seg[id].end()&&i->first<=r)
    {
        if(last+1<=i->first-1)
            Mark(last+1,i->first-1,1);
        if(i->second>r)
            break;
        Mark(i->first,i->second,-1);
        last=i->second;
        i=seg[id].erase(i);
    }
    if(i!=seg[id].end()&&i->first<=r)
    {
        Mark(i->first,r,-1);
        R=i->second;
        last=i->second;
        seg[id].erase(i);
    }
    if(last<r)
        Mark(last+1,r,1);
    seg[id].insert(make_pair(L,R));
}

int main()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int op,x,l,k,r;
        scanf("%d",&op);
        if(op==1)
        {
            scanf("%d%d%d",&x,&l,&k);
            Add(l,max(x-k,1),min(x+k,N));
        }
        else
        {
            scanf("%d%d",&l,&r);
            printf("%d\n",Query(l,r));
        }
    }

    return 0;
}
