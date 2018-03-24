#include<cstdio>
#include<vector>
using namespace std;
const long long MAXN=100005;

long long N,Q;
struct Edge
{
    long long v,w;
    Edge(long long _v,long long _w){v=_v;w=_w;}
};
struct Node
{
    long long num,sum[2];
};

Node node[MAXN*4];
long long fa[MAXN],dis[MAXN];
vector<Edge> son[MAXN];
bool blue[MAXN];
long long siz[MAXN],heav[MAXN],num;
long long pos[MAXN],id[MAXN],top[MAXN],bot[MAXN],dep[MAXN];

void dfs1(long long u,long long deep=0)
{
    siz[u]=1;
    heav[u]=0;
    dep[u]=deep;
    long long mx=0;
    for(long long i=0;i<(int)son[u].size();i++)
    {
        long long v=son[u][i].v;
        dfs1(v,deep+son[u][i].w);
        siz[u]+=siz[v];
        if(mx<siz[v])
            mx=siz[v],heav[u]=v;
    }
}
void dfs2(long long u,long long tp)
{
    pos[u]=++num;
    id[num]=u;
    top[u]=tp;
    bot[u]=u;
    if(heav[u]==0)
        return;
    dfs2(heav[u],tp);
    bot[u]=bot[heav[u]];
    for(long long i=0;i<(int)son[u].size();i++)
    {
        long long v=son[u][i].v;
        if(v!=heav[u])
            dfs2(v,v);
    }
}
void Prepare()
{
    dfs1(1);
    dfs2(1,1);
}

void Add(long long pos,long long dis,long long minL,long long maxR,long long L,long long R,long long i)
{
    if(L==R)
    {
        node[i].num++;
        node[i].sum[0]+=dis;
        node[i].sum[1]+=dis;
        return;
    }
    long long mid=(L+R)/2;
    if(pos<=mid)
        Add(pos,dis,minL,maxR,L,mid,i*2);
    else
        Add(pos,dis,minL,maxR,mid+1,R,i*2+1);
    if(L>=minL&&R<=maxR)
    {
        node[i].num=node[i*2].num+node[i*2+1].num;
        node[i].sum[0]=node[i*2].sum[0]+node[i*2+1].sum[0]+node[i*2+1].num*(dep[id[mid+1]]-dep[id[L]]);
        node[i].sum[1]=node[i*2+1].sum[1]+node[i*2].sum[1]+node[i*2].num*(dep[id[R]]-dep[id[mid]]);
    }
}
void Add(long long u)
{
    long long d=0,v,s=u;
    while(u)
    {
        Add(pos[u],d,pos[top[u]],pos[bot[u]],1,N,1);
        v=fa[top[u]];
        d=dep[s]-dep[v];
        u=v;
    }
}

pair<long long,long long> Query(long long l,long long r,long long dir,long long L,long long R,long long i)
{
    if(l>r)return make_pair(0,0);
    pair<long long,long long> res=make_pair(0,0),temp;
    if(l<=L&&R<=r)
    {
        res=make_pair(node[i].sum[dir],node[i].num);
        if(dir==0)
            res.first+=res.second*(dep[id[L]]-dep[id[l]]);
        if(dir==1)
            res.first+=res.second*(dep[id[r]]-dep[id[R]]);
        return res;
    }
    long long mid=(L+R)/2;
    if(l<=mid)
    {
        temp=Query(l,r,dir,L,mid,i*2);
        res.first+=temp.first;
        res.second+=temp.second;
    }
    if(mid<r)
    {
        temp=Query(l,r,dir,mid+1,R,i*2+1);
        res.first+=temp.first;
        res.second+=temp.second;
    }
    return res;
}
long long Query(long long u)
{
    long long s=u;
    long long d=0,v,res=0,lastv=0;
    pair<long long,long long> t1,t2,temp,last=make_pair(0,0);
    while(u)
    {
        t1=Query(pos[u],pos[bot[u]],0,1,N,1);
        t2=Query(pos[top[u]],pos[u]-1,1,1,N,1);
        temp.first=t1.first+t2.first+t2.second*dis[u]-(last.first+last.second*dis[lastv]);
        temp.second=t1.second+t2.second-last.second;
        last=Query(pos[top[u]],pos[bot[u]],0,1,N,1);
        lastv=top[u];
        res+=temp.first+temp.second*d;
        v=fa[top[u]];
        d=dep[s]-dep[v];
        u=v;
    }
    return res;
}
long long curValue, startSeed, threshold, maxDist;

long long query[MAXN][2];

long long genNextRandom() {
    curValue = (curValue * 1999 + 17) % 1000003;
    return curValue;
}

void generateInput() {
    for (long long i = 0; i < N-1; i++) {
        dis[i+2] = genNextRandom() % maxDist;
        fa[i+2] = genNextRandom();
        if (fa[i+2] < threshold) {
            fa[i+2] = i;
        } else {
            fa[i+2] = fa[i+2] % (i + 1);
        }
    }

    for (long long i = 1; i <= Q; i++) {
        query[i][0] = genNextRandom() % 2 + 1;
        query[i][1] = genNextRandom() % N + 1;
    }
}

class TreeColoring
{
public:
	long long color(int a,int b,int c,int d,int e);
};

long long TreeColoring::color(int a,int b,int c,int d,int e)
{
    N=a;
    Q=b;
    curValue=c;
    startSeed=c;
    threshold=d;
    maxDist=e;

    generateInput();

    for(long long i=2;i<=N;i++)
    {
        fa[i]++;
        son[fa[i]].push_back(Edge(i,dis[i]));
    }

    Prepare();

    long long ans=0;
    for(long long i=1;i<=Q;i++)
    {
        if(query[i][0]==1)
        {
            if(!blue[pos[query[i][1]]])
            {
                blue[pos[query[i][1]]]=true;
                Add(query[i][1]);
            }
        }
        else
            ans^=Query(query[i][1]);
    }
    return ans;
}
