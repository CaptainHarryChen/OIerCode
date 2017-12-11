#include<cstdio>
#include<set>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
const int MAXN=100005;

typedef multiset<int> Heap;
typedef vector<int> Edge;

Edge V[MAXN],gV[MAXN];

namespace LCA
{
	int fa[MAXN][20],dis[MAXN][20],lev[MAXN];
	void dfs(int u,int pa,int deep)
	{
		fa[u][0]=pa;dis[u][0]=1;lev[u]=deep;
		for(int i=0;i<(int)V[u].size();i++)
		{
			int v=V[u][i];
			if(v!=pa)
				dfs(v,u,deep+1);
		}
	}
	void init(int n)
	{
		dfs(1,0,1);
		for(int j=1;(1<<j)<n;j++)
			for(int i=1;i<=n;i++)
			{
				fa[i][j]=fa[fa[i][j-1]][j-1];
				dis[i][j]=dis[i][j-1]+dis[fa[i][j-1]][j-1];
			}
	}
	int distance(int a,int b)
	{
		if(lev[a]>lev[b])
			swap(a,b);
		int ret=0;
		for(int i=19;i>=0;i--)
			if(lev[b]-(1<<i)>=lev[a])
			{
				ret+=dis[b][i];
				b=fa[b][i];
			}
		if(a==b)return ret;
		for(int i=19;i>=0;i--)
			if(lev[a]-(1<<i)>=1&&fa[a][i]!=fa[b][i])
			{
				ret+=dis[a][i]+dis[b][i];
				a=fa[a][i],b=fa[b][i];
			}
		return ret+dis[a][0]+dis[b][0];
	}
}

Heap S1[MAXN],S2[MAXN],S;
int top2(const Heap &s)
{
	if(s.size()>=2)
	{
		Heap::reverse_iterator it=s.rbegin();
		int tmp=*it;it++;tmp+=*it;
		return tmp;
	}
	return -1;
}

int fa[MAXN],dis[MAXN];

bool vis[MAXN];
int val[MAXN],siz[MAXN],dep[MAXN];
stack<int> buf;
void calc_g(int u,int pa,int deep)
{
	buf.push(u);
	val[u]=0;siz[u]=1;dep[u]=deep;
	for(int i=0;i<(int)V[u].size();i++)
	{
		int v=V[u][i];
		if(!vis[v]&&v!=pa)
		{
			calc_g(v,u,deep+1);
			siz[u]+=siz[v];
			val[u]=max(val[u],siz[v]);
		}
	}
}
int find_g(int u)
{
	calc_g(u,0,1);
	int res,best=0x7FFFFFFF,v;
	while(!buf.empty())
	{
		v=buf.top();buf.pop();
		val[v]=max(val[v],siz[u]-siz[v]);
		if(best>val[v])
		{best=val[v];res=v;}
	}
	return res;
}
void insert(int u,int pa,int d,int rt)
{
	if(fa[rt]!=0)S1[rt].insert(dep[u]);
	for(int i=0;i<(int)V[u].size();i++)
	{
		int v=V[u][i];
		if(v==fa[rt])
			dis[rt]=d+1;
		if(!vis[v]&&v!=pa)
			insert(v,u,d+1,rt);
	}
}

void build(int n)
{
	typedef pair<int,int> point;
	static queue<point>Q;
	
	Q.push(point(1,0));
	while(!Q.empty())
	{
		point pu=Q.front();Q.pop();
		int u=pu.first,f=pu.second;
		int g=find_g(u);
		fa[g]=f;
		gV[f].push_back(g);
		if(f!=0)S1[g].insert(dep[g]);
		for(int i=0;i<(int)V[g].size();i++)
		{
			int v=V[g][i];
			if(v==f)
				dis[g]=1;
			if(!vis[v])
			{
				insert(v,g,1,g);
				Q.push(point(v,g));
			}
		}
		vis[g]=1;
	}
	
	for(int i=1;i<=n;i++)
	{
		S2[i].insert(0);
		if(fa[i]!=0)
			S2[fa[i]].insert(*S1[i].rbegin());
	}
	for(int i=1,tmp;i<=n;i++)
	{
		tmp=top2(S2[i]);
		if(tmp!=-1)
			S.insert(tmp);
	}
}

int count;
bool state[MAXN];

void Qinsert(int u)
{
	int d,g=u,tmp;
	
	tmp=top2(S2[g]);
	if(tmp!=-1)S.erase(S.find(tmp));
	S2[g].insert(0);
	tmp=top2(S2[g]);
	if(tmp!=-1)S.insert(tmp);
	
	do
	{
		if(fa[g]==0)break;
		d=LCA::distance(fa[g],u);
		
		int mx=S1[g].size()>0?*S1[g].rbegin():-1;
		S1[g].insert(d);
		if(mx<d)
		{
			tmp=top2(S2[fa[g]]);
			if(tmp!=-1)S.erase(S.find(tmp));
			Heap::iterator it=S2[fa[g]].find(mx);
			if(it!=S2[fa[g]].end())S2[fa[g]].erase(S2[fa[g]].find(mx));
			S2[fa[g]].insert(d);
			tmp=top2(S2[fa[g]]);
			if(tmp!=-1)S.insert(tmp);
		}
		
		g=fa[g];
		
	}while(g!=0);
}
void Qdelete(int u)
{
	int d,g=u,tmp;

	tmp=top2(S2[g]);
	if(tmp!=-1)S.erase(S.find(tmp));
	S2[g].erase(S2[g].find(0));
	tmp=top2(S2[g]);
	if(tmp!=-1)S.insert(tmp);
	
	do
	{
		if(fa[g]==0)break;
		d=LCA::distance(fa[g],u);
		
		tmp=top2(S2[fa[g]]);
		if(tmp!=-1)S.erase(S.find(tmp));
		S2[fa[g]].erase(S2[fa[g]].find(*S1[g].rbegin()));
		Heap::iterator it=S1[g].find(d);
		if(it!=S1[g].end())S1[g].erase(S1[g].find(d));
		if(S1[g].size()>0)S2[fa[g]].insert(*S1[g].rbegin());
		tmp=top2(S2[fa[g]]);
		if(tmp!=-1)S.insert(tmp);
		
		g=fa[g];
	}while(g!=0);
}
int Qquery()
{
	if(count==1)
		return 0;
	if(count==0)
		return -1;
	return *S.rbegin();
}

int main()
{
	int n,a,b,Q;
	char op[5];
	
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		V[a].push_back(b);
		V[b].push_back(a);
	}
	
	LCA::init(n);
	build(n);
	
	count=n;
	scanf("%d",&Q);
	for(int q=1,i;q<=Q;q++)
	{
		scanf("%s",op);
		if(op[0]=='C')
		{
			scanf("%d",&i);
			if(state[i])
			{
				state[i]=false;
				count++;
				Qinsert(i);
			}
			else
			{
				state[i]=true;
				count--;
				Qdelete(i);
			}
		}
		else
			printf("%d\n",Qquery());
	}
	return 0;
}
