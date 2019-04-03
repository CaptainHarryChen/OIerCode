#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=400005;

#ifdef LOCAL
#define __int128 long long
#endif

template<class T>
void read(T &x){
    x=0;
    int f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    x=x*f;
}


template<class T>
void print(T x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}


struct Edge
{int v,w;};

int n;
int fa[MAXN];
long long dp1[MAXN],dp2[MAXN],d,dep[MAXN];
__int128 ans;
bool dia[MAXN];
vector<Edge> adj[MAXN];

void dfs(int u)
{
	for(auto &e:adj[u])
		if(e.v!=fa[u])
		{
			fa[e.v]=u;
			dep[e.v]=dep[u]+e.w;
			dfs(e.v);
		}
}
long long dfs2(int u,int f,long long dp[])
{
	long long mx=0,mx2=0;
	dp[u]=0;
	for(auto &e:adj[u])
		if(e.v!=f)
		{
			long long tmp=dfs2(e.v,u,dp)+e.w;
			if(tmp>mx)
				mx2=mx,mx=tmp;
			else if(tmp>mx2)
				mx2=tmp;
			dp[u]=max(dp[u],dp[e.v]);
		}
	dp[u]=max(dp[u],mx+mx2);
	return mx;
}
void dfs3(int u,int f)
{
	for(auto &e:adj[u])
		if(e.v!=f)
		{
			if(dia[u]&&dia[e.v])
				ans=max(ans,(__int128)dp1[u]*dp2[e.v]);
            else
				ans=max(ans,(__int128)d*dp1[e.v]);
            dfs3(e.v,u);
		}
}

void solve()
{
    memset(fa,0,sizeof fa);
    memset(dep,0,sizeof dep);
    memset(dp1,0,sizeof dp1);
    memset(dp2,0,sizeof dp2);
    memset(dia,0,sizeof dia);

    dfs(1);
	int mx=1,mx2=1;
	for(int i=2;i<=n;i++)
		if(dep[i]>dep[mx])
			mx=i;
	fa[mx]=dep[mx]=0;
	dfs(mx);
	for(int i=2;i<=n;i++)
		if(dep[i]>dep[mx2])
			mx2=i;
	for(int u=mx2;u!=mx;u=fa[u])
		dia[u]=true;
	dia[mx]=true;
	d=dep[mx2];
	dfs2(mx,0,dp1);
	dfs2(mx2,0,dp2);
	dfs3(mx2,0);
}

int main()
{
    read(n);
    for(int i=1,u,v,w;i<n;i++)
    {
        read(u);read(v);read(w);
        adj[u].push_back(Edge{v,w});
        adj[v].push_back(Edge{u,w});
    }

    solve();
    for(int i=1;i<=n;i++)
        for(auto &e:adj[i])
            e.w*=-1;
    solve();

    print(ans);

    return 0;
}
