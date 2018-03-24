#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int MAXN=200005,MAXK=1000005;
 
struct Edge
{
    int v,w;
    Edge(int _v,int _w){v=_v;w=_w;}
};
 
int n,k;
vector<Edge> adj[MAXN];
 
int dfn1[MAXN],dfn2[MAXN],dfc;
int siz[MAXN],id[MAXN],lev[MAXN],son[MAXN];
long long dep[MAXN];
 
void init(int u,int fa=0,long long deep=0,int level=0)
{
    siz[u]=1;
    dfn1[u]=++dfc;
    id[dfc]=u;
    dep[u]=deep;
    lev[u]=level;
    int mx=0;
    for(int i=0;i<(int)adj[u].size();i++)
        if(adj[u][i].v!=fa)
        {
            int v=adj[u][i].v;
            init(v,u,deep+adj[u][i].w,level+1);
            siz[u]+=siz[v];
            if(mx<siz[v])
                mx=siz[v],son[u]=v;
        }
    dfn2[u]=dfc;
}
 
int ans=0x7FFFFFFF;
map<long long,int> best;
 
void dsu(int u,int fa=0,bool keep=false)
{
    for(int i=0;i<(int)adj[u].size();i++)
        if(adj[u][i].v!=fa&&adj[u][i].v!=son[u])
        {
            int v=adj[u][i].v;
            dsu(v,u,false);
        }
    if(son[u])
        dsu(son[u],u,true);
	if(best.count(dep[u]))
		best[dep[u]]=min(best[dep[u]],lev[u]);
	else
		best[dep[u]]=lev[u];
	/*puts("DEBUG_BEGIN");
	for(map<long long,int>::iterator it=best.begin();it!=best.end();it++)
		printf("best[%I64d]=%d\n",it->first,it->second);
	puts("DEBUG_END");*/
	if(best.count(dep[u]+k))
		ans=min(ans,best[dep[u]+k]-lev[u]);
    for(int i=0;i<(int)adj[u].size();i++)
        if(adj[u][i].v!=fa&&adj[u][i].v!=son[u])
        {
            int v=adj[u][i].v;
			for(int t=dfn1[v];t<=dfn2[v];t++)
				if(best.count(k-(dep[id[t]]-dep[u])+dep[u]))
					ans=min(ans,lev[id[t]]+best[k-(dep[id[t]]-dep[u])+dep[u]]-2*lev[u]);
            for(int t=dfn1[v];t<=dfn2[v];t++)
            {
				if(best.count(dep[id[t]]))
					best[dep[id[t]]]=min(best[dep[id[t]]],lev[id[t]]);
				else
					best[dep[id[t]]]=lev[id[t]];
            }
        }
    if(keep==false)
		best.clear();
}
 
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1,u,v,w;i<n;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        u++;v++;
        adj[u].push_back(Edge(v,w));
        adj[v].push_back(Edge(u,w));
    }
	
    init(1);
    dsu(1);
	
    printf("%d\n",ans==0x7FFFFFFF?-1:ans);
	
    return 0;
}
