#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const long long MAXN=2505;
long long n;
long long G[MAXN][MAXN];
long long ecnt;
struct Edge
{
	long long u,v,val;
	Edge(){}
	Edge(long long _u,long long _v,long long _val):u(_u),v(_v),val(_val){}
}ed[MAXN*MAXN];
bool cmp(Edge a,Edge b)
{return a.val<b.val;}
long long S[MAXN];
long long root(long long x)
{
	if(S[x]==0)
		return x;
	return S[x]=root(S[x]);
}
vector<long long>V[MAXN],W[MAXN];
bool check(long long st,long long u,long long mx=0,long long fa=-1)
{
	if(mx!=G[st][u])
		return false;
	for(long long i=0;i<V[u].size();i++)
		if(V[u][i]!=fa)
			if(!check(st,V[u][i],max(mx,W[u][i]),u))
				return false;
	return true;
}
int main()
{
	scanf("%I64d",&n);
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=n;j++)
		{
			scanf("%I64d",G[i]+j);
			if((i==j&&G[i][j]!=0)||(i>j&&(G[i][j]!=G[j][i])))
			{
				printf("NOT MAGIC\n");
				return 0;
			}
			if(i>j)
				ed[++ecnt]=Edge(i,j,G[i][j]);
		}
	sort(ed+1,ed+ecnt+1,cmp);
	long long r1,r2,cnt=0;
	for(long long it=1;it<=ecnt&&cnt<n-1;it++)
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
		printf("NOT MAGIC\n");
		return 0;
	}
	bool flag=true;
	for(long long i=1;i<=n;i++)
		if(!check(i,i))
		{
			flag=false;
			break;
		}
	if(flag)
		printf("MAGIC\n");
	else
		printf("NOT MAGIC\n");
	return 0;
}
