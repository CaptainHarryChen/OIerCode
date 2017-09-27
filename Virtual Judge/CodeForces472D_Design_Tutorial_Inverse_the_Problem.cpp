#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN=2005;
int n;
int G[MAXN][MAXN];
int ecnt;
struct Edge
{
	int u,v,val;
	Edge(){}
	Edge(int _u,int _v,int _val):u(_u),v(_v),val(_val){}
}ed[MAXN*MAXN];
bool cmp(Edge a,Edge b)
{return a.val<b.val;}
int S[MAXN];
int root(int x)
{
	if(S[x]==0)
		return x;
	return S[x]=root(S[x]);
}
vector<int>V[MAXN],W[MAXN];
bool dfs(int st,int u,int dis=0,int fa=-1)
{
	if(dis!=G[st][u])
		return false;
	for(int i=0;i<V[u].size();i++)
		if(V[u][i]!=fa)
			if(!dfs(st,V[u][i],dis+W[u][i],u))
				return false;
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",G[i]+j);
			if((i==j&&G[i][j]!=0)||(i>j&&(G[i][j]!=G[j][i]||G[i][j]==0)))
			{
				printf("NO\n");
				return 0;
			}
			if(i>j)
				ed[++ecnt]=Edge(i,j,G[i][j]);
		}
	sort(ed+1,ed+ecnt+1,cmp);
	int r1,r2,cnt=0;
	for(int it=1;it<=ecnt&&cnt<n-1;it++)
	{
		r1=root(ed[it].u);
		r2=root(ed[it].v);
		if(r1!=r2)
		{
			cnt++;
			S[r1]=r2;
			V[ed[it].u].push_back(ed[it].v);
			W[ed[it].u].push_back(ed[it].val);
			V[ed[it].v].push_back(ed[it].u);
			W[ed[it].v].push_back(ed[it].val);
		}
	}
	if(cnt!=n-1)
	{
		printf("NO\n");
		return 0;
	}
	bool flag=true;
	for(int i=1;i<=n;i++)
		if(!dfs(i,i))
		{
			flag=false;
			break;
		}
	if(flag)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
