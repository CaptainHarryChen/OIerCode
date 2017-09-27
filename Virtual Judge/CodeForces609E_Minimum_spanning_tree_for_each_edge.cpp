#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=200005,MAXM=200005;
struct Edge
{
	int u,v,val,id;
	bool operator < (const Edge &t)const
	{return val<t.val;}
};
bool number(const Edge &a,const Edge &b)
{return a.id<b.id;}
struct Edge_list
{
	int v,val,id;
	Edge_list *next;
	Edge_list(){}
	Edge_list(int _v,int _val,int _id)
	{next=NULL,v=_v,val=_val,id=_id;}
};
class LCAtree
{
private:
	int fa[MAXN][20],val[MAXN][20],mlog;
	int lev[MAXN];
	Edge_list E[MAXM*2],*cur;
	void dfs(int u,int f,int level)
	{
		for(Edge_list *p=V[u];p;p=p->next)
			if(p->v!=f)
			{
				lev[p->v]=level+1;
				fa[p->v][0]=u;
				val[p->v][0]=p->val;
				dfs(p->v,u,level+1);
			}
	}
public:
	Edge_list *V[MAXN];
	LCAtree()
	{cur=E;}
	void add_edge(const Edge &t)
	{
		*cur=Edge_list(t.v,t.val,t.id);
		cur->next=V[t.u];
		V[t.u]=cur++;
		*cur=Edge_list(t.u,t.val,t.id);
		cur->next=V[t.v];
		V[t.v]=cur++;
	}
	void Init(int n)
	{
		dfs(1,0,0);
		for(int j=1;(1<<j)<=n;j++)
		{
			mlog=j;
			for(int i=1;i<=n;i++)
				if(lev[i]>=(1<<j))
				{
					fa[i][j]=fa[fa[i][j-1]][j-1];
					val[i][j]=max(val[i][j-1],val[fa[i][j-1]][j-1]);
				}
		}
	}
	int LCA(int a,int b,int &mx)
	{
		mx=0;
		if(lev[a]<lev[b])
			swap(a,b);
		for(int i=mlog;i>=0;i--)
			if(lev[a]-(1<<i)>=lev[b])
			{
				mx=max(mx,val[a][i]);
				a=fa[a][i];
			}
		if(a==b)
			return a;
		for(int i=mlog;i>=0;i--)
			if(lev[a]-(1<<i)>=0&&fa[a][i]!=fa[b][i])
			{
				mx=max(mx,max(val[a][i],val[b][i]));
				a=fa[a][i];
				b=fa[b][i];
			}
		mx=max(mx,max(val[a][0],val[b][0]));
		return fa[a][0];
	}
};
class UFset
{
private:
	int fa[MAXN];
public:
	int Find(int x)
	{
		if(fa[x]==0)
			return x;
		return fa[x]=Find(fa[x]);
	}
	void Union(int x,int y)
	{fa[x]=y;}
};
Edge E[MAXM];
bool used[MAXM];
UFset U;
LCAtree L;
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].val);
		E[i].id=i;
	}
	sort(E+1,E+m+1);
	int r1,r2;
	long long W=0;
	for(int i=1;i<=m;i++)
	{
		r1=U.Find(E[i].u);
		r2=U.Find(E[i].v);
		if(r1!=r2)
		{
			W+=E[i].val;
			used[E[i].id]=true;
			U.Union(r1,r2);
			L.add_edge(E[i]);
		}
	}
	sort(E+1,E+m+1,number);
	L.Init(n);
	int mx;
	for(int i=1;i<=m;i++)
		if(used[i])
			printf("%I64d\n",W);
		else
		{
			L.LCA(E[i].u,E[i].v,mx);
			printf("%I64d\n",W-mx+E[i].val);
		}
	return 0;
}
